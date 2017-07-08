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

#include <QtDebug>
#include "currency.h"

Currency::Currency() : data(new CurrencyData)
{

}

Currency::Currency(const Currency &rhs) : data(rhs.data)
{

}

Currency &Currency::operator=(const Currency &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Currency::Currency(CurrencySign::Sign sign, uint integralPart, quint16 fractonalPart, quint16 code):
   data(new CurrencyData(((qint64)sign)*(integralPart*10000+(qint64)fractonalPart), code))
{

}

Currency::Currency(qint64 integralPart, quint16 fractonalPart, quint16 code):
    data(new CurrencyData(integralPart*10000+(integralPart<0?-1:1)*fractonalPart, code))
{

}

Currency::Currency(double amount, uint code):
    data(new CurrencyData((qint64)(amount*10000), code))
{
}

Currency::~Currency()
{

}

bool Currency::isPositive() const
{
    return data->v<0?false:true;
}

qint64 Currency::mils() const
{
    return data->v;
}

qint64 Currency::integralPart() const
{
    return data->v/10000;
}

qint64 Currency::integralPartAbs() const
{
    return qAbs(data->v/10000);
}

quint16 Currency::fractionalPart() const
{
    return qAbs(data->v%10000);
}

double Currency::fractionalPartAsDouble() const
{
    return ((double)data->v/10000)-(qint64)data->v/10000;
}

quint16 Currency::fractionalIntegerPart() const
{
    return qAbs((data->v%10000)/100);
}

quint16 Currency::fractionalFractionalPart() const
{
    return qAbs(data->v%100);
}

quint16 Currency::code() const
{
    return data->c;
}

Currency &Currency::clear()
{
    data->c= 0;
    data->v= 0;
    return *this;
}

Currency &Currency::codeSet(quint16 code)
{
    data->c= code;
    return *this;
}

Currency &Currency::increment(uint integralPart, quint16 fractonalPart)
{
    data->v+= integralPart*10000+fractonalPart;
    return *this;
}

Currency &Currency::decrement(uint integralPart, quint16 fractonalPart)
{
    data->v-= integralPart*10000+fractonalPart;
    return *this;
}

Currency &Currency::multiply(uint integralPart, quint16 fractonalPart)
{
    data->v= (data->v * (integralPart*10000+fractonalPart))/10000;
    return *this;
}

Currency &Currency::divide(uint integralPart, quint16 fractonalPart)
{
    data->v= data->v*10000/(integralPart*10000+fractonalPart);
    return *this;
}

