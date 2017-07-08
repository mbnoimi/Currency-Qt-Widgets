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

#ifndef CURRENCYLABEL_H
#define CURRENCYLABEL_H

#include <QFrame>
#include <QLabel>

#include "currency.h"
#include "currencywidgetsdef.h"

class CurrencyLabel : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(bool positive READ positive )

public:
    explicit CurrencyLabel(CurrencyDisplayNameFormat::Format nameFormat= CurrencyDisplayNameFormat::Symbol,
                  CurrencyDisplayNamePosition::Position namePosition= CurrencyDisplayNamePosition::End,
                  CurrencyDisplaySeparator::Separator separatorMode= CurrencyDisplaySeparator::Locale,
                  QWidget * parent = 0, Qt::WindowFlags f = 0);
   explicit  CurrencyLabel(const Currency& currency,
                  CurrencyDisplayNameFormat::Format nameFormat= CurrencyDisplayNameFormat::Symbol,
                  CurrencyDisplayNamePosition::Position namePosition= CurrencyDisplayNamePosition::End,
                  CurrencyDisplaySeparator::Separator separatorMode= CurrencyDisplaySeparator::Locale,
                  QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~CurrencyLabel();

    Currency currency() const;
    bool positive() const;
    int separatorMode();

public slots:
    void updateDisplay();
    void clearDisplay();
    void nameSet(const QString &name);
    void currencySet(const Currency& currency);
    void separatorModeSet(int separatorMode);
    void nameFormatSet(int nameFormat);
    void namePositionSet(int namePosition);

private:
    Currency aCurrency;
    CurrencyDisplayNameFormat::Format aNameFormat;
    CurrencyDisplayNamePosition::Position aNamePosition;
    CurrencyDisplaySeparator::Separator aSeparatorMode;

    QLabel *aSymBegin;
    QLabel *aSign;
    QLabel *aIntPart;
    QLabel *aSep;
    QLabel *aFracPart;
    QLabel *aSymEnd;

    inline void updateNamePosition();
    inline void updateSeparator();
    void init();
    void doLayout();
};

#endif // CURRENCYLABEL_H
