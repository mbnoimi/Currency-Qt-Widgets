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

#include <QString>
#include <QObject>
#include "currencyinfo.h"

class CurrencyInfoData : public QSharedData
{
public:
    CurrencyInfoData()
        :n(QObject::tr("No Currency"))
        ,lc(QObject::tr("XXX")),nc(999), s(QChar(0x00A4)){}
    CurrencyInfoData(QString name, QString letterCode,
    quint16 numericCode, QString symbol):
        n(name), lc(letterCode), nc(numericCode), s(symbol)
    {}
    QString n; // currency name
    QString lc; // 3-letter code
    quint16 nc; //numeric code
    QString s; // currency symbol

};
Q_DECLARE_METATYPE(CurrencyInfoData)

CurrencyInfo::CurrencyInfo() : data(new CurrencyInfoData)
{

}

CurrencyInfo::CurrencyInfo(const CurrencyInfo &rhs) : data(rhs.data)
{

}

CurrencyInfo::CurrencyInfo(QString name, QString letterCode, quint16 numericCode, QString symbol)
: data(new CurrencyInfoData(name, letterCode, numericCode, symbol))
{

}

CurrencyInfo &CurrencyInfo::operator=(const CurrencyInfo &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

CurrencyInfo::~CurrencyInfo()
{

}

bool CurrencyInfo::isNull()
{
    if(data->nc==0
       || data->lc.isEmpty()
       || data->n.isEmpty()) return true;
return false;
}

QString CurrencyInfo::name() const
{
    return data->n;
}

QString CurrencyInfo::letterCode() const
{
    return data->lc;
}

quint16 CurrencyInfo::numCode() const
{
    return data->nc;
}

QString CurrencyInfo::numCodeString() const
{
    return QString::number(data->nc).prepend("00").right(3);
}

QString CurrencyInfo::symbol() const
{
    return data->s;
}

QString CurrencyInfo::symbolOrLetterCode() const
{
    return data->s.isEmpty()?data->lc:data->s;
}

