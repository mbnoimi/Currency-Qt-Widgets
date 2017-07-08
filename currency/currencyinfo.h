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

#ifndef CURRENCYINFO_H
#define CURRENCYINFO_H

#include <QMetaType>
#include <QSharedDataPointer>

class CurrencyInfoData;

class CurrencyInfo
{
public:
    CurrencyInfo();
    CurrencyInfo(const CurrencyInfo &);
    CurrencyInfo(QString name
             ,QString letterCode, quint16 numericCode, QString symbol);
    CurrencyInfo &operator=(const CurrencyInfo &);
    ~CurrencyInfo();
    bool isNull();
    QString name() const;
    QString letterCode() const;
    quint16 numCode() const;
    QString numCodeString() const;
    QString symbol() const;
    QString symbolOrLetterCode() const;

private:
    QSharedDataPointer<CurrencyInfoData> data;
};
Q_DECLARE_METATYPE(CurrencyInfo)

typedef QList<CurrencyInfo> CurrencyInfoList;
Q_DECLARE_METATYPE(CurrencyInfoList)


#endif // CURRENCYINFO_H
