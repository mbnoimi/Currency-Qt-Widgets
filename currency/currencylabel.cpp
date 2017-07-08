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

#include <QLocale>
#include <QHBoxLayout>

#include <QtDebug>

#include "currencylabel.h"
#include "currencyinfodir.h"

CurrencyLabel::CurrencyLabel(CurrencyDisplayNameFormat::Format nameFormat,
                             CurrencyDisplayNamePosition::Position namePosition,
                             CurrencyDisplaySeparator::Separator separatorMode,
                             QWidget * parent, Qt::WindowFlags f)
    :QFrame(parent,f),aNameFormat(nameFormat),aNamePosition(namePosition),aSeparatorMode(separatorMode)
{
    init();
    doLayout();
}

CurrencyLabel::CurrencyLabel(const Currency &currency,
                             CurrencyDisplayNameFormat::Format nameFormat,
                             CurrencyDisplayNamePosition::Position namePosition,
                             CurrencyDisplaySeparator::Separator separatorMode,
                             QWidget *parent, Qt::WindowFlags f)
    :QFrame(parent,f),aCurrency(currency),aNameFormat(nameFormat),aNamePosition(namePosition),aSeparatorMode(separatorMode)
{
    init();
    doLayout();
}

CurrencyLabel::~CurrencyLabel()
{

}

Currency CurrencyLabel::currency() const
{
    return aCurrency;
}

void CurrencyLabel::currencySet(const Currency &currency)
{
    aCurrency= currency;
    updateDisplay();
}

void CurrencyLabel::separatorModeSet(int separatorMode)
{
    aSeparatorMode= (CurrencyDisplaySeparator::Separator)separatorMode;
    updateDisplay();
}

void CurrencyLabel::nameFormatSet(int nameFormat)
{
    aNameFormat= (CurrencyDisplayNameFormat::Format)nameFormat;
    updateDisplay();
}

void CurrencyLabel::namePositionSet(int namePosition)
{
    aNamePosition= (CurrencyDisplayNamePosition::Position)namePosition;
    updateDisplay();
}

bool CurrencyLabel::positive() const
{
    return aCurrency.isPositive();
}

int CurrencyLabel::separatorMode()
{
    return aSeparatorMode;
}

void CurrencyLabel::updateDisplay()
{
    CurrencyInfo ci= CurrencyInfoDir::infoByNumericCode(aCurrency.code());
    clearDisplay();
    updateSeparator();
    updateNamePosition();
    if(!CurrencyInfoDir::exists(aCurrency.code())){
        aIntPart->setText(QString::number(aCurrency.integralPartAbs()));
        aFracPart->setText(QString::number(aCurrency.fractionalPart()));
        aSymEnd->setText(tr("Not Currency"));
    }else{
        aSign->setText(aCurrency.isPositive()?"":"-");
        aIntPart->setText(QString::number(aCurrency.integralPartAbs()));
        aFracPart->setText(QString::number(aCurrency.fractionalPart()).prepend("000").right(4));
        nameSet(aNameFormat==CurrencyDisplayNameFormat::Symbol?
                    ci.symbol():(aNameFormat==CurrencyDisplayNameFormat::LetterCode?
                                     ci.letterCode():(aNameFormat==CurrencyDisplayNameFormat::Name?
                                                          ci.name():ci.numCodeString())
                                     )
                    );
    }
    if(aSign->text().isEmpty()) aSign->hide();
    else aSign->show();
    QString css= styleSheet();
    setStyleSheet("");
    setStyleSheet(css);
}

void CurrencyLabel::clearDisplay()
{
    aSymBegin->clear();
    aSign->clear();
    aIntPart->clear();
    aSep->clear();
    aFracPart->clear();
    aFracPart->clear();
    aSymEnd->clear();
}

void CurrencyLabel::nameSet(const QString &name)
{
    if(aNamePosition == CurrencyDisplayNamePosition::Middle) aSep->setText(name);
    else{
        aSymBegin->setText(name);
        aSymEnd->setText(name);
    }
}

void CurrencyLabel::updateNamePosition()
{
    switch (aNamePosition) {
    case CurrencyDisplayNamePosition::Begin:
        aSymBegin->show();
        aSymEnd->hide();
        break;
    case CurrencyDisplayNamePosition::Middle:
        aSymBegin->hide();
        aSymEnd->hide();
        break;
    default:
        aSymBegin->hide();
        aSymEnd->show();
        break;
    }
}

void CurrencyLabel::updateSeparator()
{
    switch (aSeparatorMode) {
    case CurrencyDisplaySeparator::Dot:
        aSep->setText(".");
        break;
    case CurrencyDisplaySeparator::Comma:
        aSep->setText(",");
        break;
    case CurrencyDisplaySeparator::Dash:
        aSep->setText("-");
        break;
    default:
        aSep->setText(QLocale::system().decimalPoint());
        break;
    }
}

void CurrencyLabel::init()
{
    aSymBegin= new QLabel();
    aSymBegin->setObjectName("Symbol");
    aSign= new QLabel();
    aSign->setObjectName("Sign");
    aIntPart= new QLabel();
    aIntPart->setObjectName("IntPart");
    aSep= new QLabel();
    aSep->setObjectName("Separator");
    aFracPart= new QLabel();
    aFracPart->setObjectName("FractPart");
    aSymEnd= new QLabel();
    aSymEnd->setObjectName("Symbol");
}

void CurrencyLabel::doLayout()
{
    QHBoxLayout *lt= new QHBoxLayout();
    lt->addWidget(aSymBegin);
    lt->addWidget(aSign);
    lt->addWidget(aIntPart);
    lt->addWidget(aSep);
    lt->addWidget(aFracPart);
    lt->addWidget(aSymEnd);
    lt->addStretch(1);

    lt->setSpacing(2);
    lt->setMargin(0);
    setLayout(lt);

    updateDisplay();
}

