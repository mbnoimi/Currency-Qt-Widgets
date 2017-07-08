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

#include <QTextEdit>
#include <QTextBlock>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QTabWidget>
#include <QComboBox>
#include <QPushButton>

#include <QtDebug>

#include "currencydemo.h"
#include "currency/currencyinfodir.h"
#include "currency/currencylabel.h"
#include "currency/currencylineedit.h"

CurrencyDemo::CurrencyDemo(QWidget *parent)
    : QWidget(parent)
{
    if(QMetaType::type("Currency")==QMetaType::UnknownType)qRegisterMetaType<Currency>(new Currency());
    if(QMetaType::type("CurrencyInfo")==QMetaType::UnknownType)qRegisterMetaType<CurrencyInfo>(new CurrencyInfo());
    if(QMetaType::type("CurrencyInfoList")==QMetaType::UnknownType)qRegisterMetaType<CurrencyInfoList>(new CurrencyInfoList());

    QLabel *editL= new QLabel(tr("   Currency Input"));
    editL->setStyleSheet("QLabel{color: white; background-color:#3382f7; font-weight: bold;}");
    editL->setFixedHeight(24);

    CurrencyInfoList cil;
    cil<<CurrencyInfoDir::infoByLetterCode("UAH")
       <<CurrencyInfoDir::infoByLetterCode("USD")
       <<CurrencyInfoDir::infoByLetterCode("EUR")
       <<CurrencyInfoDir::infoByLetterCode("RUB")
       <<CurrencyInfoDir::infoByLetterCode("GEL")
       <<CurrencyInfoDir::infoByLetterCode("KZT")
       <<CurrencyInfoDir::infoByLetterCode("KRW")
       <<CurrencyInfoDir::infoByLetterCode("IRR")
       <<CurrencyInfoDir::infoByLetterCode("ILS");

    cle= new CurrencyLineEdit(cil);
    cle->setObjectName("lineEdit");
    cle->setFixedWidth(75);

    QLabel *editSepL= new QLabel(tr("Separator:"));
    QComboBox *editSep= new QComboBox();
    editSep->addItems(QStringList()<<"Locale"<<"Dot"<<"Comma"<<"Dash");
    connect(editSep, SIGNAL(currentIndexChanged(int)), cle, SLOT(separatorModeSet(int)));

    QLabel *displayL= new QLabel(tr("   Currency Display"));
    displayL->setStyleSheet(editL->styleSheet());
    displayL->setFixedHeight(24);

    cl= new CurrencyLabel(Currency(CurrencySign::Minus,999,8991,
                                   CurrencyInfoDir::infoByLetterCode("ANG").numCode()),
                          CurrencyDisplayNameFormat::Symbol,
                          CurrencyDisplayNamePosition::End,
                          CurrencyDisplaySeparator::Dash);
    cl->setObjectName("label");

    cl->setStyleSheet("CurrencyLabel {background-color: lightyellow; border-bottom: 1px solid lightgray;} "
                      "CurrencyLabel[positive=\"false\"] QLabel {color: darkred;font-size: 12px;} "
                      "CurrencyLabel[positive=\"true\"] QLabel {color: blue;font-size: 12px;} "
                      "#Sign {color: magenta; font-weight: bold;} "
                      "#IntPart {color: blue; font-size: 14px; font-weight: bold;} "
                      "#Separator {color: darkgray; font-weight: bold;} "
                      "#FractPart {font-size: 10px;} "
                      "#Symbol {color: green;} "
                      );

    QLabel *lSepL= new QLabel(tr("Separator:"));
    QComboBox *lSep= new QComboBox();
    lSep->addItems(QStringList()<<"Locale"<<"Dot"<<"Comma"<<"Dash");
    lSep->setCurrentIndex(3);
    connect(lSep, SIGNAL(currentIndexChanged(int)), cl, SLOT(separatorModeSet(int)));

    QLabel *lNameFL= new QLabel(tr("Name format:"));
    QComboBox *lNameF= new QComboBox();
    lNameF->addItems(QStringList()<<"LetterCode"<<"NumericCode"<<"Symbol"<<"Name");
    lNameF->setCurrentIndex(2);
    connect(lNameF, SIGNAL(currentIndexChanged(int)), cl, SLOT(nameFormatSet(int)));

    QLabel *lNamePL= new QLabel(tr("Name position:"));
    QComboBox *lNameP= new QComboBox();
    lNameP->addItems(QStringList()<<"Begin"<<"Middle"<<"End");
    lNameP->setCurrentIndex(2);
    connect(lNameP, SIGNAL(currentIndexChanged(int)), cl, SLOT(namePositionSet(int)));

    QLabel *lStyleL= new QLabel(tr("Style sheet"));
    lStyle= new QTextEdit(cl->styleSheet().replace("}","}<br>"));
    QPushButton *lStyleB= new QPushButton(tr("Apply"));
    connect(lStyleB, &QPushButton::clicked, this, &CurrencyDemo::onStyleApply);

    QLabel *mathL= new QLabel(tr("   Currency Math"));
    mathL->setStyleSheet(editL->styleSheet());
    mathL->setFixedHeight(24);

    aPlus1= new CurrencyLineEdit();
    aPlus1->setFixedWidth(100);
    connect(editSep, SIGNAL(currentIndexChanged(int)), aPlus1, SLOT(separatorModeSet(int)));
    aPlus2= new CurrencyLineEdit();
    aPlus2->setFixedWidth(100);
    connect(editSep, SIGNAL(currentIndexChanged(int)), aPlus2, SLOT(separatorModeSet(int)));
    QLabel *plusL= new QLabel(tr("+"));
    plusL->setFixedWidth(10);
    QPushButton *plusB= new QPushButton(tr("="));
    plusB->setFixedWidth(24);
    aPlusResL= new CurrencyLabel(CurrencyDisplayNameFormat::Symbol,
                                 CurrencyDisplayNamePosition::End,
                                 CurrencyDisplaySeparator::Dash);
    aPlusResL->setStyleSheet(cl->styleSheet());
    connect(lSep, SIGNAL(currentIndexChanged(int)), aPlusResL, SLOT(separatorModeSet(int)));
    connect(lNameF, SIGNAL(currentIndexChanged(int)), aPlusResL, SLOT(nameFormatSet(int)));
    connect(lNameP, SIGNAL(currentIndexChanged(int)), aPlusResL, SLOT(namePositionSet(int)));
    connect(plusB, &QPushButton::clicked, this, &CurrencyDemo::onPlusB);

    aMinus1= new CurrencyLineEdit();
    aMinus1->setFixedWidth(100);
    connect(editSep, SIGNAL(currentIndexChanged(int)), aMinus1, SLOT(separatorModeSet(int)));
    aMinus2= new CurrencyLineEdit();
    aMinus2->setFixedWidth(100);
    connect(editSep, SIGNAL(currentIndexChanged(int)), aMinus2, SLOT(separatorModeSet(int)));
    QLabel *minusL= new QLabel(tr("-"));
    minusL->setFixedWidth(10);
    QPushButton *minusB= new QPushButton(tr("="));
    minusB->setFixedWidth(24);
    aMinusResL= new CurrencyLabel(CurrencyDisplayNameFormat::Symbol,
                                 CurrencyDisplayNamePosition::End,
                                 CurrencyDisplaySeparator::Dash);
    aMinusResL->setStyleSheet(cl->styleSheet());
    connect(lSep, SIGNAL(currentIndexChanged(int)), aMinusResL, SLOT(separatorModeSet(int)));
    connect(lNameF, SIGNAL(currentIndexChanged(int)), aMinusResL, SLOT(nameFormatSet(int)));
    connect(lNameP, SIGNAL(currentIndexChanged(int)), aMinusResL, SLOT(namePositionSet(int)));
    connect(minusB, &QPushButton::clicked, this, &CurrencyDemo::onMinusB);

    // init settings widget
    aCurrencyInfoModel= new QStandardItemModel();
    aCurrencyInfoModel->setColumnCount(5);
    aCurrencyInfoModel->setRowCount(257);
    int r=0;

    for(int c=1; c<258; c++)
    {
        CurrencyInfo ci=  CurrencyInfoDir::currencyForCountry((QLocale::Country)c);
        QStandardItem *itm= new QStandardItem(ci.letterCode());
        itm->setCheckable(true);
        aCurrencyInfoModel->setItem(r,0,itm);
        itm= new QStandardItem(ci.numCodeString());
        aCurrencyInfoModel->setItem(r,1,itm);
        itm= new QStandardItem(ci.symbol());
        aCurrencyInfoModel->setItem(r,2,itm);
        itm= new QStandardItem(ci.name());
        aCurrencyInfoModel->setItem(r,3,itm);
        itm= new QStandardItem(QLocale::countryToString((QLocale::Country)c));
        aCurrencyInfoModel->setItem(r,4,itm);
        ++r;
    }

    QLabel *cfgL= new QLabel(tr("   Operational currencies"));
    cfgL->setStyleSheet(editL->styleSheet());
    cfgL->setFixedHeight(24);

    QTableView *tv= new QTableView();
    tv->setModel(aCurrencyInfoModel);
    tv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tv->horizontalHeader()->adjustSize();
    tv->horizontalHeader()->hide();
    tv->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    tv->verticalHeader()->setDefaultSectionSize(22);
    tv->verticalHeader()->hide();

    QPushButton *tvB= new QPushButton(tr("Apply"));
    connect(tvB, &QPushButton::clicked, this, &CurrencyDemo::onCurrencyListUpdate);


    connect(cle, &CurrencyLineEdit::changed, cl, &CurrencyLabel::currencySet);
    cl->currencySet(Currency(CurrencySign::Minus,9,9999,CurrencyInfoDir::infoByLetterCode("ANG").numCode()));

    QWidget *aDemoW= new QWidget();

    QHBoxLayout *elt= new QHBoxLayout();
    elt->addWidget(cle);
    elt->addWidget(editSepL);
    elt->addWidget(editSep);
    elt->addStretch(1);

    QHBoxLayout *llt= new QHBoxLayout();
    llt->addWidget(cl);
    llt->addStretch(1);

    QHBoxLayout *lplt= new QHBoxLayout();
    lplt->addWidget(lSepL);
    lplt->addWidget(lSep);
    lplt->addWidget(lNameFL);
    lplt->addWidget(lNameF);
    lplt->addWidget(lNamePL);
    lplt->addWidget(lNameP);
    lplt->addStretch(1);

    QHBoxLayout *lslt= new QHBoxLayout();
    lslt->addWidget(lStyle,1);
    lslt->addWidget(lStyleB);

    QHBoxLayout *plusLt= new QHBoxLayout();
    plusLt->addWidget(aPlus1);
    plusLt->addWidget(plusL);
    plusLt->addWidget(aPlus2);
    plusLt->addWidget(plusB);
    plusLt->addWidget(aPlusResL);
    plusLt->addStretch(1);

    QHBoxLayout *minusLt= new QHBoxLayout();
    minusLt->addWidget(aMinus1);
    minusLt->addWidget(minusL);
    minusLt->addWidget(aMinus2);
    minusLt->addWidget(minusB);
    minusLt->addWidget(aMinusResL);
    minusLt->addStretch(1);


    QVBoxLayout *demoLt= new QVBoxLayout();
    demoLt->addWidget(editL);
    demoLt->addLayout(elt);
    demoLt->addWidget(displayL);
    demoLt->addLayout(llt);
    demoLt->addLayout(lplt);
    demoLt->addWidget(lStyleL);
    demoLt->addLayout(lslt);
    demoLt->addWidget(mathL);
    demoLt->addLayout(plusLt);
    demoLt->addLayout(minusLt);
    demoLt->addStretch(1);

    aDemoW->setLayout(demoLt);

    QWidget *aCfgW= new QWidget();

    QVBoxLayout *cfgLt= new QVBoxLayout();
    cfgLt->addWidget(cfgL);
    cfgLt->addWidget(tv,1);
    cfgLt->addWidget(tvB);

    aCfgW->setLayout(cfgLt);

    QTabWidget *aTabW= new QTabWidget();
    aTabW->addTab(aDemoW, tr("Demo"));
    aTabW->addTab(aCfgW, tr("Settings"));

    QVBoxLayout *lt= new QVBoxLayout();
    lt->addWidget(aTabW);
    setLayout(lt);
    resize(600,600);
}

CurrencyDemo::~CurrencyDemo()
{

}

void CurrencyDemo::onStyleApply()
{
    cl->setStyleSheet(lStyle->toPlainText());
    aPlusResL->setStyleSheet(lStyle->toPlainText());
    aMinusResL->setStyleSheet(lStyle->toPlainText());
}

void CurrencyDemo::onCurrencyListUpdate()
{
    CurrencyInfoList c;
    for(int r=0; r<aCurrencyInfoModel->rowCount(); r++)
        if(aCurrencyInfoModel->item(r)->checkState()==Qt::Checked)
            c<<CurrencyInfoDir::infoByNumericCode(aCurrencyInfoModel->item(r,1)->text().toInt());
    cle->currencyInfosSet(c);
    aPlus1->currencyInfosSet(c);
    aPlus2->currencyInfosSet(c);
    aMinus1->currencyInfosSet(c);
    aMinus2->currencyInfosSet(c);
}

void CurrencyDemo::onPlusB()
{
    aPlusResL->currencySet(aPlus1->currency()+aPlus2->currency());
}

void CurrencyDemo::onMinusB()
{
    aMinusResL->currencySet(aMinus1->currency()-aMinus2->currency());
}
