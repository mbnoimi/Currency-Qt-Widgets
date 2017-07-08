/*
 * This file is part of the Currency software
 *
 * Copyright (C) 2014 Denis Kvita <dkvita@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <QRegExpValidator>
#include <QCompleter>
#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>

#include <QtDebug>

#include "currencylineedit.h"
#include "currencyinfodir.h"


CurrencyLineEdit::CurrencyLineEdit(const CurrencyInfoList & c,
                                   CurrencyDisplaySeparator::Separator separatorMode,
                                   QWidget *parent)
    : QLineEdit(parent),aSeparatorMode(separatorMode)
{
    aIntRx= "(-{0,1}[0-9]+)";
    updateSeparator();
    aFracRx= "([0-9]{1,4})";
    aSymbolPrtRx= "([a-zA-Z]{0,3})";
    aSymbolCmplRx= "([a-zA-Z]{3})";

    QRegExpValidator *v= new QRegExpValidator(QRegExp(aIntRx+"\\s{0,1}"+aSepRx+"\\s{0,1}"+aFracRx+"\\s{1}"+aSymbolCmplRx));
    setValidator(v);

    currencyInfosSet(c);

    connect(this, &CurrencyLineEdit::textEdited, this, &CurrencyLineEdit::onTextEdited);
}

CurrencyLineEdit::~CurrencyLineEdit()
{

}

Currency CurrencyLineEdit::currency()
{
    return aCurrency;
}

void CurrencyLineEdit::separatorModeSet(int separatorMode)
{
    QString t= text();
    QString rxs;
    if(hasAcceptableInput()){
        rxs= ""+aIntRx+"\\s{0,1}"+aSepRx+"\\s{0,1}"+aFracRx+"\\s{1}"+aSymbolCmplRx;
    }else t.clear();

    aSeparatorMode= (CurrencyDisplaySeparator::Separator)separatorMode;
    updateSeparator();
    QRegExpValidator *v= new QRegExpValidator(QRegExp(aIntRx
                                                      +"\\s{0,1}"+aSepRx+"\\s{0,1}"
                                                      +aFracRx+"\\s{1}"+aSymbolCmplRx));
    setValidator(v);

    if(!t.isEmpty()){
        QRegExp rx(rxs);
        rx.indexIn(t);
        t= rx.cap(1)+aSepRx.right(1)+rx.cap(2)+" "+rx.cap(3);
    }
    setText(t);
}

void CurrencyLineEdit::currencyInfosSet(const CurrencyInfoList &c)
{
    QStandardItemModel *aCompleterModel= new QStandardItemModel();
    aCompleterModel->setColumnCount(3);

    int r=0;
    if(c.count()<=0){
        aCompleterModel->setRowCount(CurrencyInfoDir::numericCodes().count());
        foreach(QString lc, CurrencyInfoDir::letterCodes()){
            CurrencyInfo ci= CurrencyInfoDir::infoByLetterCode(lc);
            QStandardItem *itm= new QStandardItem(ci.letterCode());
            aCompleterModel->setItem(r,0,itm);
            itm= new QStandardItem(ci.symbol());
            aCompleterModel->setItem(r,1,itm);
            itm= new QStandardItem(ci.name());
            aCompleterModel->setItem(r,2,itm);
            ++r;
        }
    }else{
        aCompleterModel->setRowCount(c.count());
        foreach (CurrencyInfo ci, c) {
            QStandardItem *itm= new QStandardItem(ci.letterCode());
            aCompleterModel->setItem(r,0,itm);
            itm= new QStandardItem(ci.symbol());
            aCompleterModel->setItem(r,1,itm);
            itm= new QStandardItem(ci.name());
            aCompleterModel->setItem(r,2,itm);
            ++r;
        };
    }

    QTableView *tv= new QTableView();
    tv->setModel(aCompleterModel);
    tv->horizontalHeader()->adjustSize();
    tv->horizontalHeader()->hide();
    tv->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    tv->verticalHeader()->setDefaultSectionSize(22);
    tv->verticalHeader()->hide();

    QCompleter *cpr= new QCompleter(this);
    cpr->setCompletionMode(QCompleter::PopupCompletion);
    cpr->setCaseSensitivity(Qt::CaseInsensitive);
    cpr->setWidget(this);
    cpr->setModel(aCompleterModel);
    cpr->setCompletionColumn(0);
    cpr->setPopup(tv);
    cpr->setMaxVisibleItems(15);
    aCompleter= cpr;
    connect(aCompleter, SIGNAL(activated(QString)), this, SLOT(onCompleterActivated(QString)));

}

void CurrencyLineEdit::onCompleterActivated(const QString &text)
{
    QString t= this->text();
    QRegExp rx("("+aIntRx+"\\s{0,1}"+aSepRx+"\\s{0,1}"+aFracRx+"\\s{1})"+aSymbolPrtRx);
    int ci= rx.indexIn(t);
    QString c= ci !=-1 ? rx.cap(4) : "";
    t.replace(rx.cap(1).length(),c.length(), text);
    setText(t);
    if(hasAcceptableInput()){
        int ip= rx.cap(2).toInt();
        quint16 fp= rx.cap(3).append("0000").left(4).toUInt();
        Currency c= Currency((rx.cap(2).left(1)=="-"?CurrencySign::Minus:CurrencySign::Plus),
                             qAbs(ip),fp,CurrencyInfoDir::infoByLetterCode(text).numCode());
        if(aCurrency!=c){
            aCurrency= c;
            emit changed(aCurrency);
        }
    }
}

void CurrencyLineEdit::updateSeparator()
{
    switch (aSeparatorMode) {
    case CurrencyDisplaySeparator::Dot:
        aSepRx= QRegExp::escape(".");
        break;
    case CurrencyDisplaySeparator::Comma:
        aSepRx= QRegExp::escape(",");
        break;
    case CurrencyDisplaySeparator::Dash:
        aSepRx= QRegExp::escape("-");
        break;
    default:
        aSepRx= QRegExp::escape(QLocale::system().decimalPoint());
        break;
    }
    setPlaceholderText("0"+aSepRx.right(1)+"00 "+QChar(0x00a4));
}

void CurrencyLineEdit::onTextEdited(const QString &text)
{
    QRegExp rx(aIntRx+"\\s{0,1}"+aSepRx+"\\s{0,1}"+aFracRx+"(\\s{1})"+aSymbolPrtRx);
    int ci= rx.indexIn(text);
    QString c= ci !=-1 ? rx.cap(3) : "";
    if(!rx.cap(3).isEmpty() && cursorPosition()>=text.length()){
        aCompleter->setCompletionPrefix(rx.cap(4));
        bool popupMove= !aCompleter->popup()->isVisible() ? true : false;
        if(popupMove){
            QRect cr= cursorRect();
            cr.setSize(aCompleter->popup()->sizeHint());
            cr.setHeight(22*aCompleter->maxVisibleItems());
            cr.moveTo(QPoint(cr.bottomLeft().x(),geometry().height()));
            aCompleter->complete(cr);
            aCompleter->popup()->move(mapToGlobal(cr.topLeft()));
        }
        if(aCompleter->completionCount()>0) aCompleter->popup()->setCurrentIndex(
                    aCompleter->model()->index(0,0));
    }else aCompleter->popup()->hide();
    if(hasAcceptableInput()){
        QRegExp rx("("+aIntRx+"\\s{0,1}"+aSepRx+"\\s{0,1}"+aFracRx+"\\s{1})"+aSymbolCmplRx);
        rx.indexIn(text);
        int ip= rx.cap(2).toInt();
        quint16 fp= rx.cap(3).append("0000").left(4).toUInt();
        Currency c= Currency((rx.cap(2).left(1)=="-"?CurrencySign::Minus:CurrencySign::Plus),
                             qAbs(ip),fp,CurrencyInfoDir::infoByLetterCode(rx.cap(4)).numCode());
        if(aCurrency!=c){
            aCurrency= c;
            emit changed(aCurrency);
        }
    }
}

