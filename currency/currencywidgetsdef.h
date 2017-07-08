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

#ifndef CURRENCYWIDGETSDEF_H
#define CURRENCYWIDGETSDEF_H

namespace CurrencyDisplayNameFormat {
enum Format{
    LetterCode=0
    ,NumericCode
    ,Symbol
    ,Name
};
}

namespace CurrencyDisplayNamePosition {
enum Position{
    Begin=0
    ,Middle
    ,End
};
}

namespace CurrencyDisplaySeparator {
enum Separator{
    Locale=0
    ,Dot
    ,Comma
    ,Dash
};
}

#endif // CURRENCYWIDGETSDEF_H

