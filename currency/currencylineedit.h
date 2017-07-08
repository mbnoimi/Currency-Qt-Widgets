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

#ifndef CIRRENCYLINEEDIT_H
#define CIRRENCYLINEEDIT_H

#include <QLineEdit>

#include "currencywidgetsdef.h"
#include "currency.h"
#include "currencyinfo.h"

class QCompleter;

class CurrencyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit CurrencyLineEdit(const CurrencyInfoList & c = CurrencyInfoList(),
                              CurrencyDisplaySeparator::Separator separatorMode= CurrencyDisplaySeparator::Locale,
                              QWidget *parent = 0);
    ~CurrencyLineEdit();
    Currency currency();

signals:
    void changed(Currency c);

public slots:
    void separatorModeSet(int separatorMode);
    void currencyInfosSet(const CurrencyInfoList & c);
    void onTextEdited(const QString & text);
    void onCompleterActivated(const QString &text);

protected:
    void updateSeparator();

private:
    QString aIntRx, aSepRx, aFracRx, aSymbolPrtRx, aSymbolCmplRx;
    QCompleter *aCompleter;
    Currency aCurrency;
    CurrencyDisplaySeparator::Separator aSeparatorMode;
};

#endif // CIRRENCYLINEEDIT_H
