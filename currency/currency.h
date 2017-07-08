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

#ifndef CURRENCY_H
#define CURRENCY_H

#include <QMetaType>
#include <QSharedDataPointer>

namespace CurrencySign {
enum Sign{
    Plus=1
    ,Minus=-1
};
}

class CurrencyData : public QSharedData
{
public:
    CurrencyData():v(0),c(0){}
    CurrencyData(qint64 value, quint16 code):
        v(value), c(code)
    {}
    qint64 v; // currency value in the 1/10000 parts of the main currency unit
    quint16 c; // numeric code

};
Q_DECLARE_METATYPE(CurrencyData)

class Currency
{
public:
    Currency();
    Currency(const Currency &);
    Currency &operator=(const Currency &);
    Currency(CurrencySign::Sign sign, uint integralPart, quint16 fractonalPart, quint16 code);
    Currency(qint64 integralPart, quint16 fractonalPart, quint16 code);
    Currency(double amount, uint code);
    ~Currency();
    bool isPositive() const;
    qint64 mils() const;
    qint64 integralPart() const;
    qint64 integralPartAbs() const;
    quint16 fractionalPart() const;
    double fractionalPartAsDouble() const;
    quint16 fractionalIntegerPart() const;
    quint16 fractionalFractionalPart() const;
    quint16 code() const;
    Currency& clear();

    Currency& codeSet(quint16 code);
    Currency& increment(uint integralPart, quint16 fractonalPart);
    Currency& decrement(uint integralPart, quint16 fractonalPart);
    Currency& multiply(uint integralPart, quint16 fractonalPart);
    Currency& divide(uint integralPart, quint16 fractonalPart);

    inline bool operator==(const Currency &other) {
        if(this == &other ||
           this->data == other.data ||
           (this->data->v == other.data->v && this->data->c == other.data->c)
           ) return true;
        return false;
    }
    inline bool operator!=(const Currency &other) { return !operator ==(other); }

    inline Currency &operator+=(const Currency &c){
        if(c.code()!=code()) clear();
        else data->v+= c.data->v;
        return *this;
        }

    inline Currency &operator-=(const Currency &c){
        if(c.code()!=code()) clear();
        else data->v-= c.data->v;
        return *this;
    }

    operator int() const { return data->v/10000;}
    operator double() const {return (double)data->v/10000;}

private:
    QSharedDataPointer<CurrencyData> data;
};
Q_DECLARE_METATYPE(Currency)


inline const Currency operator+(const Currency &s1, const Currency &s2)
{ Currency t(s1); t += s2; return t; }

inline const Currency operator-(const Currency &s1, const Currency &s2)
{ Currency t(s1); t -= s2; return t; }

#endif // CURRENCY_H
