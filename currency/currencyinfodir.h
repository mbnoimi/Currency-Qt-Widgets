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

#ifndef CURRENCYINFODIR_H
#define CURRENCYINFODIR_H

#include <QHash>
#include <QLocale>

#include "currencyinfo.h"

class CurrencyInfoDir
{
public:
    static const CurrencyInfo infoByNumericCode(quint16 numericCode);
    static const CurrencyInfo infoByLetterCode(QString letterCode);
    static const CurrencyInfo currencyForCountry(QLocale::Country country);
    static const QList<quint16> numericCodes();
    static const QStringList letterCodes();
    static const QStringList names();
    static const QStringList symbols();
    static bool exists(quint16 numericCode);
    static bool exists(const QString& letterCode);

private:
   CurrencyInfoDir(){} // Private so that it can  not be called
   CurrencyInfoDir(CurrencyInfoDir const&){} // copy constructor is private
   CurrencyInfoDir& operator=(CurrencyInfoDir const&){return *this;} // assignment operator is private
   static void init();
   static QHash<quint16,CurrencyInfo> aInfo;
   static QHash<QLocale::Country,quint16> aCountry;
};

#endif // CURRENCYINFODIR_H
