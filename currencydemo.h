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

#ifndef CURRENCYDEMO_H
#define CURRENCYDEMO_H

#include <QWidget>

class CurrencyLabel;
class CurrencyLineEdit;
class QTextEdit;
class QStandardItemModel;

class CurrencyDemo : public QWidget
{
    Q_OBJECT

public:
    CurrencyDemo(QWidget *parent = 0);
    ~CurrencyDemo();

public slots:
    void onStyleApply();
    void onCurrencyListUpdate();
    void onPlusB();
    void onMinusB();

private:
    CurrencyLineEdit *cle;
    CurrencyLabel *cl;
    QTextEdit *lStyle;
    QStandardItemModel *aCurrencyInfoModel;
    CurrencyLineEdit *aPlus1;
    CurrencyLineEdit *aPlus2;
    CurrencyLabel *aPlusResL;

    CurrencyLineEdit *aMinus1;
    CurrencyLineEdit *aMinus2;
    CurrencyLabel *aMinusResL;
};

#endif // CURRENCYDEMO_H
