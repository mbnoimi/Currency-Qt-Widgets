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

#include <QObject>

#include "currencyinfodir.h"
#include "currencyinfo.h"

// Global static instance used to ensure a single instance of the class.
QHash<quint16,CurrencyInfo> CurrencyInfoDir::aInfo= QHash<quint16,CurrencyInfo>();
QHash<QLocale::Country,quint16> CurrencyInfoDir::aCountry= QHash<QLocale::Country,quint16>();

const CurrencyInfo CurrencyInfoDir::infoByNumericCode(quint16 numericCode)
{
    if(aInfo.count()<=0) init();
    return aInfo.value(numericCode, CurrencyInfo());
}

const CurrencyInfo CurrencyInfoDir::infoByLetterCode(QString letterCode)
{
    if(aInfo.count()<=0) init();
    foreach (quint16 nc, aInfo.keys()) {
        CurrencyInfo ci= aInfo.value(nc);
        if(ci.letterCode()==letterCode) return aInfo.value(nc);
    }
    return CurrencyInfo();
}

const CurrencyInfo CurrencyInfoDir::currencyForCountry(QLocale::Country country)
{
    if(aInfo.count()<=0) init();
    if(!aCountry.contains(country)) return CurrencyInfo();
    return aInfo.value(aCountry.value(country));
}

const QList<quint16> CurrencyInfoDir::numericCodes()
{
    if(aInfo.count()<=0) init();
    return aInfo.keys();
}

const QStringList CurrencyInfoDir::letterCodes()
{
    if(aInfo.count()<=0) init();
    QStringList l;
    foreach (CurrencyInfo ci, aInfo.values()) {
        l<< ci.letterCode();
    }
    qSort(l);
    return l;
}

const QStringList CurrencyInfoDir::names()
{
    if(aInfo.count()<=0) init();
    QStringList l;
    foreach (CurrencyInfo ci, aInfo.values()) {
        l<< ci.name();
    }
    qSort(l);
    return l;
}

const QStringList CurrencyInfoDir::symbols()
{
    if(aInfo.count()<=0) init();
    QStringList l;
    foreach (CurrencyInfo ci, aInfo.values()) {
        if(!l.contains(ci.symbol()))l<< ci.symbol();
    }
    qSort(l);
    return l;
}

bool CurrencyInfoDir::exists(quint16 numericCode)
{
    if(aInfo.count()<=0) init();
    return aInfo.contains(numericCode);
}

bool CurrencyInfoDir::exists(const QString &letterCode)
{
    if(aInfo.count()<=0) init();
    return infoByLetterCode(letterCode).letterCode()==letterCode;
}

void CurrencyInfoDir::init()
{
    aInfo.insert(971,CurrencyInfo(QObject::tr("Afghani"),QObject::tr("AFN"),971,QChar(0x060B)));
    aCountry.insert(QLocale::Afghanistan, 971);
    aInfo.insert(978,CurrencyInfo(QObject::tr("Euro"),QObject::tr("EUR"),978,QChar(0x20AC)));
    aCountry.insert(QLocale::AlandIslands, 978);
    aCountry.insert(QLocale::Andorra, 978);
    aCountry.insert(QLocale::Austria, 978);
    aCountry.insert(QLocale::Belgium, 978);
    aCountry.insert(QLocale::Cyprus, 978);
    aCountry.insert(QLocale::Estonia, 978);
    aCountry.insert(QLocale::Finland, 978);
    aCountry.insert(QLocale::France, 978);
    aCountry.insert(QLocale::FrenchGuiana, 978);
    aCountry.insert(QLocale::FrenchSouthernTerritories, 978);
    aCountry.insert(QLocale::Germany, 978);
    aCountry.insert(QLocale::Greece, 978);
    aCountry.insert(QLocale::Guadeloupe, 978);
    aCountry.insert(QLocale::VaticanCityState, 978);
    aCountry.insert(QLocale::Ireland, 978);
    aCountry.insert(QLocale::Italy, 978);
    aCountry.insert(QLocale::Latvia, 978);
    aCountry.insert(QLocale::Luxembourg, 978);
    aCountry.insert(QLocale::Malta, 978);
    aCountry.insert(QLocale::Martinique, 978);
    aCountry.insert(QLocale::Mayotte, 978);
    aCountry.insert(QLocale::Monaco, 978);
    aCountry.insert(QLocale::Montenegro, 978);
    aCountry.insert(QLocale::Netherlands, 978);
    aCountry.insert(QLocale::Portugal, 978);
    aCountry.insert(QLocale::Reunion, 978);
    aCountry.insert(QLocale::SaintBarthelemy, 978);
    aCountry.insert(QLocale::SaintMartin, 978);
    aCountry.insert(QLocale::SaintPierreAndMiquelon, 978);
    aCountry.insert(QLocale::SanMarino, 978);
    aCountry.insert(QLocale::Slovakia, 978);
    aCountry.insert(QLocale::Slovenia, 978);
    aCountry.insert(QLocale::Spain, 978);
    aCountry.insert(QLocale::Kosovo, 978);
    //    aCountry.insert(QLocale::, 978);

    aInfo.insert(8,CurrencyInfo(QObject::tr("Lek"),QObject::tr("ALL"),8,QString("L")));
    aCountry.insert(QLocale::Albania, 8);
    aInfo.insert(12,CurrencyInfo(QObject::tr("Algerian Dinar"),QObject::tr("DZD"),12,QString("DA")));
    aCountry.insert(QLocale::Algeria, 12);
    aInfo.insert(840,CurrencyInfo(QObject::tr("US Dollar"),QObject::tr("USD"),840,QChar(0x0024)));
    aCountry.insert(QLocale::AmericanSamoa, 840);
    aCountry.insert(QLocale::Bonaire, 840);
    aCountry.insert(QLocale::Ecuador, 840);
    aCountry.insert(QLocale::Guam, 840);
    aCountry.insert(QLocale::MarshallIslands, 840);
    aCountry.insert(QLocale::Micronesia, 840);
    aCountry.insert(QLocale::NorthernMarianaIslands, 840);
    aCountry.insert(QLocale::Palau, 840);
    //    aCountry.insert(QLocale::Panama, 840);
    aCountry.insert(QLocale::PuertoRico, 840);
    aCountry.insert(QLocale::TurksAndCaicosIslands, 840);
    aCountry.insert(QLocale::UnitedStates, 840);
    aCountry.insert(QLocale::UnitedStatesMinorOutlyingIslands, 840);
    //    aCountry.insert(QLocale::, 840);
    aCountry.insert(QLocale::BritishIndianOceanTerritory, 840);
    aCountry.insert(QLocale::BritishVirginIslands, 840);
    aCountry.insert(QLocale::UnitedStatesVirginIslands, 840);

    aInfo.insert(973,CurrencyInfo(QObject::tr("Kwanza"),QObject::tr("AOA"),973,QString("Kz")));
    aCountry.insert(QLocale::Angola, 973);
    aInfo.insert(951,CurrencyInfo(QObject::tr("East Caribbean Dollar"),QObject::tr("XCD"),951,QString("$")));
    aCountry.insert(QLocale::Anguilla, 951);
    aCountry.insert(QLocale::AntiguaAndBarbuda, 951);
    aCountry.insert(QLocale::Dominica, 951);
    aCountry.insert(QLocale::Grenada, 951);
    aCountry.insert(QLocale::Montserrat, 951);
    aCountry.insert(QLocale::SaintKittsAndNevis, 951);
    aCountry.insert(QLocale::SaintLucia, 951);
    aCountry.insert(QLocale::SaintVincentAndTheGrenadines, 951);

    aInfo.insert(32,CurrencyInfo(QObject::tr("Argentine Peso"),QObject::tr("ARS"),32,QChar(0x0024)));
    aCountry.insert(QLocale::Argentina, 32);
    aInfo.insert(51,CurrencyInfo(QObject::tr("Armenian Dram"),QObject::tr("AMD"),51,QChar(0x058F)));
    aCountry.insert(QLocale::Armenia, 51);
    aInfo.insert(533,CurrencyInfo(QObject::tr("Aruban Florin"),QObject::tr("AWG"),533,QChar(0x0192)));
    aCountry.insert(QLocale::Aruba, 533);
    aInfo.insert(36,CurrencyInfo(QObject::tr("Australian Dollar"),QObject::tr("AUD"),36,QChar(0x24)));
    aCountry.insert(QLocale::Australia, 36);
    aCountry.insert(QLocale::ChristmasIsland, 36);
    aCountry.insert(QLocale::CocosIslands, 36);
    aCountry.insert(QLocale::HeardAndMcDonaldIslands, 36);
    aCountry.insert(QLocale::Kiribati, 36);
    aCountry.insert(QLocale::NauruCountry, 36);
    aCountry.insert(QLocale::NorfolkIsland, 36);
    aCountry.insert(QLocale::Tuvalu, 36);

    aInfo.insert(944,CurrencyInfo(QObject::tr("Azerbaijanian Manat"),QObject::tr("AZN"),944,QString("%1%2%3").arg(QChar(0x043c)).arg(QChar(0x0430)).arg(QChar(0x043d))));
    aCountry.insert(QLocale::Azerbaijan, 944);
    aInfo.insert(44,CurrencyInfo(QObject::tr("Bahamian Dollar"),QObject::tr("BSD"),44,QChar(0x0024)));
    aCountry.insert(QLocale::Bahamas, 44);
    aInfo.insert(48,CurrencyInfo(QObject::tr("Bahraini Dinar"),QObject::tr("BHD"),48,QString("BD")));
    aCountry.insert(QLocale::Bahrain, 48);
    aInfo.insert(50,CurrencyInfo(QObject::tr("Taka"),QObject::tr("BDT"),50,QChar(0x00A4)));
    aCountry.insert(QLocale::Bangladesh, 50);
    aInfo.insert(52,CurrencyInfo(QObject::tr("Barbados Dollar"),QObject::tr("BBD"),52,QChar(0x0024)));
    aCountry.insert(QLocale::Barbados, 52);
    aInfo.insert(974,CurrencyInfo(QObject::tr("Belarussian Ruble"),QObject::tr("BYR"),974,QString("%1%2").arg(QChar(0x0070)).arg(QChar(0x002E))));
    aCountry.insert(QLocale::Belarus, 974);
    aInfo.insert(84,CurrencyInfo(QObject::tr("Belize Dollar"),QObject::tr("BZD"),84,QString("%1%2%3").arg(QChar(0x0042)).arg(QChar(0x005A)).arg(QChar(0x0024))));
    aCountry.insert(QLocale::Belize, 84);
    aInfo.insert(952,CurrencyInfo(QObject::tr("CFA Franc BCEAO"),QObject::tr("XOF"),952,QString("CFA")));
    aCountry.insert(QLocale::Benin, 952);
    aCountry.insert(QLocale::BurkinaFaso, 952);
    aCountry.insert(QLocale::IvoryCoast, 952);
    aCountry.insert(QLocale::GuineaBissau, 952);
    aCountry.insert(QLocale::Mali, 952);
    aCountry.insert(QLocale::Niger, 952);
    aCountry.insert(QLocale::Senegal, 952);
    aCountry.insert(QLocale::Togo, 952);
    //    aCountry.insert(QLocale::, 952);

    aInfo.insert(60,CurrencyInfo(QObject::tr("Bermudian Dollar"),QObject::tr("BMD"),60,QChar(0x24)));
    aCountry.insert(QLocale::Bermuda, 60);
    aInfo.insert(64,CurrencyInfo(QObject::tr("Ngultrum"),QObject::tr("BTN"),64,QString("Nu.")));
    aCountry.insert(QLocale::Bhutan, 64);
    // and rupee
    aInfo.insert(68,CurrencyInfo(QObject::tr("Boliviano"),QObject::tr("BOB"),68,QString("%1%2").arg(QChar(0x0024)).arg(QChar(0x0062))));
    aCountry.insert(QLocale::Bolivia, 68);
    // and Mvdol
    aInfo.insert(977,CurrencyInfo(QObject::tr("Convertible Mark"),QObject::tr("BAM"),977,QString("%1%2").arg(QChar(0x004b)).arg(QChar(0x004d))));
    aCountry.insert(QLocale::BosniaAndHerzegowina, 977);
    aInfo.insert(72,CurrencyInfo(QObject::tr("Pula"),QObject::tr("BWP"),72,QChar(0x0050)));
    aCountry.insert(QLocale::Botswana, 72);
    aInfo.insert(578,CurrencyInfo(QObject::tr("Norwegian Krone"),QObject::tr("NOK"),578,QString("%1%2").arg(QChar(0x006b)).arg(QChar(0x0072))));
    aCountry.insert(QLocale::BouvetIsland, 578);
    aCountry.insert(QLocale::Norway, 578);
    aCountry.insert(QLocale::SvalbardAndJanMayenIslands, 578);

    //aInfo.insert(986,CurrencyInfo(QObject::tr("Brazilian Cruzeiro"),QObject::tr("BRZ"),986,QChar(0x20a2))); // historical
    aInfo.insert(986,CurrencyInfo(QObject::tr("Brazilian Real"),QObject::tr("BRL"),986,QString("%1%2").arg(QChar(0x0052)).arg(QChar(0x0024))));
    aCountry.insert(QLocale::Brazil, 986);
    aInfo.insert(96,CurrencyInfo(QObject::tr("Brunei Dollar"),QObject::tr("BND"),96,QChar(0x0024)));
    aCountry.insert(QLocale::Brunei, 96);
    aInfo.insert(975,CurrencyInfo(QObject::tr("Bulgarian Lev"),QObject::tr("BGN"),975,QString("%1%2").arg(QChar(0x043b)).arg(QChar(0x0432))));
    aCountry.insert(QLocale::Bulgaria, 975);
    aInfo.insert(108,CurrencyInfo(QObject::tr("Burundi Franc"),QObject::tr("BIF"),108,QString("FBu")));
    aCountry.insert(QLocale::Burundi, 108);
    aInfo.insert(116,CurrencyInfo(QObject::tr("Riel"),QObject::tr("KHR"),116,QChar(0x17db)));
    aCountry.insert(QLocale::Cambodia, 116);
    aInfo.insert(950,CurrencyInfo(QObject::tr("CFA Franc BEAC"),QObject::tr("XAF"),950,QString("FCFA")));
    aCountry.insert(QLocale::Cameroon, 950);
    aCountry.insert(QLocale::CentralAfricanRepublic, 950);
    aCountry.insert(QLocale::Chad, 950);
    aCountry.insert(QLocale::EquatorialGuinea, 950);
    aCountry.insert(QLocale::Gabon, 950);
    aCountry.insert(QLocale::CongoBrazzaville, 950);

    //aCountry.insert(QLocale::CongoBrazzaville, 950);
    aInfo.insert(124,CurrencyInfo(QObject::tr("Canadian Dollar"),QObject::tr("CAD"),124,QChar(0x0024)));
    aCountry.insert(QLocale::Canada, 124);
    aInfo.insert(132,CurrencyInfo(QObject::tr("Cabo Verde Escudo"),QObject::tr("CVE"),132,QChar(0x00A4)));
    //    aCountry.insert(QLocale::, );
    aInfo.insert(136,CurrencyInfo(QObject::tr("Cayman Islands Dollar"),QObject::tr("KYD"),136,QChar(0x0024)));
    aCountry.insert(QLocale::CaymanIslands, 136);
    aInfo.insert(990,CurrencyInfo(QObject::tr("Unidad de Fomento"),QObject::tr("CLF"),990,QChar(0x00A4)));
    aInfo.insert(152,CurrencyInfo(QObject::tr("Chilean Peso"),QObject::tr("CLP"),152,QChar(0x0024)));
    //aCountry.insert(QLocale::Chile, 990);
    aCountry.insert(QLocale::Chile, 152);
    aInfo.insert(156,CurrencyInfo(QObject::tr("Yuan Renminbi"),QObject::tr("CNY"),156,QChar(0x00A5)));
    aCountry.insert(QLocale::China, 156);
    aInfo.insert(170,CurrencyInfo(QObject::tr("Colombian Peso"),QObject::tr("COP"),170,QChar(0x24)));
    aCountry.insert(QLocale::Colombia, 170);
    aInfo.insert(970,CurrencyInfo(QObject::tr("Unidad de Valor Real"),QObject::tr("COU"),970,QChar(0x00A4)));
    //aCountry.insert(QLocale::Colombia, );
    aInfo.insert(174,CurrencyInfo(QObject::tr("Comoro Franc"),QObject::tr("KMF"),174,QString("CF")));
    aCountry.insert(QLocale::Comoros, 174);
    aInfo.insert(976,CurrencyInfo(QObject::tr("Congolese Franc"),QObject::tr("CDF"),976,QString("FC")));
    aCountry.insert(QLocale::CongoKinshasa, 976);
    aInfo.insert(554,CurrencyInfo(QObject::tr("New Zealand Dollar"),QObject::tr("NZD"),554,QChar(0x0024)));
    aCountry.insert(QLocale::NewZealand, 554);
    aCountry.insert(QLocale::Niue, 554);
    aCountry.insert(QLocale::Pitcairn, 554);
    aCountry.insert(QLocale::Tokelau, 554);
    aCountry.insert(QLocale::CookIslands, 554);

    aInfo.insert(188,CurrencyInfo(QObject::tr("Costa Rican Colon"),QObject::tr("CRC"),188,QChar(0x20A1)));
    aCountry.insert(QLocale::CostaRica, 188);
    aInfo.insert(191,CurrencyInfo(QObject::tr("Croatian Kuna"),QObject::tr("HRK"),191,QString("%1%2").arg(QChar(0x006b)).arg(QChar(0x006e))));
    aCountry.insert(QLocale::Croatia, 191);
    aInfo.insert(931,CurrencyInfo(QObject::tr("Peso Convertible"),QObject::tr("CUC"),931,QChar(0x00A4)));
    aInfo.insert(192,CurrencyInfo(QObject::tr("Cuban Peso"),QObject::tr("CUP"),192,QChar(0x20b1)));
    aCountry.insert(QLocale::Cuba, 192);
    aInfo.insert(532,CurrencyInfo(QObject::tr("Netherlands Antillean Guilder"),QObject::tr("ANG"),532,QChar(0x0192)));
    aCountry.insert(QLocale::CuraSao, 532);
    aCountry.insert(QLocale::SintMaarten, 532);

    aInfo.insert(203,CurrencyInfo(QObject::tr("Czech Koruna"),QObject::tr("CZK"),203,QString("%1%2").arg(QChar(0x004b)).arg(QChar(0x010d))));
    aCountry.insert(QLocale::CzechRepublic, 203);
    aInfo.insert(208,CurrencyInfo(QObject::tr("Danish Krone"),QObject::tr("DKK"),208,QString("%1%2").arg(QChar(0x006b)).arg(QChar(0x0072))));
    aCountry.insert(QLocale::Denmark, 208);
    aCountry.insert(QLocale::FaroeIslands, 208);
    aCountry.insert(QLocale::Greenland, 208);

    aInfo.insert(262,CurrencyInfo(QObject::tr("Djibouti Franc"),QObject::tr("DJF"),262,QString("Fdj")));
    aCountry.insert(QLocale::Djibouti, 262);
    aInfo.insert(214,CurrencyInfo(QObject::tr("Dominican Peso"),QObject::tr("DOP"),214,QString("%1%2%3").arg(QChar(0x0052)).arg(QChar(0x0044)).arg(QChar(0x0024))));
    aCountry.insert(QLocale::DominicanRepublic, 214);
    aInfo.insert(818,CurrencyInfo(QObject::tr("Egyptian Pound"),QObject::tr("EGP"),818,QChar(0x00a3)));
    aCountry.insert(QLocale::Egypt, 818);
    aInfo.insert(222,CurrencyInfo(QObject::tr("El Salvador Colon"),QObject::tr("SVC"),222,QChar(0x24)));
    aCountry.insert(QLocale::ElSalvador, 818);
    //    aCountry.insert(QLocale::ElSalvador, 840);
    aInfo.insert(232,CurrencyInfo(QObject::tr("Nakfa"),QObject::tr("ERN"),232,QString("Nfk")));
    aCountry.insert(QLocale::Eritrea, 232);
    aInfo.insert(230,CurrencyInfo(QObject::tr("Ethiopian Birr"),QObject::tr("ETB"),230,QString("Br")));
    aCountry.insert(QLocale::Ethiopia, 230);
    aInfo.insert(238,CurrencyInfo(QObject::tr("Falkland Islands Pound"),QObject::tr("FKP"),238,QChar(0x00a3)));
    aCountry.insert(QLocale::FalklandIslands, 238);
    aInfo.insert(242,CurrencyInfo(QObject::tr("Fiji Dollar"),QObject::tr("FJD"),242,QChar(0x0024)));
    aCountry.insert(QLocale::Fiji, 242);
    aInfo.insert(953,CurrencyInfo(QObject::tr("CFP Franc"),QObject::tr("XPF"),953,QString("F")));
    aCountry.insert(QLocale::FrenchPolynesia, 953);
    aCountry.insert(QLocale::NewCaledonia, 953);
    aCountry.insert(QLocale::WallisAndFutunaIslands, 953);
    aCountry.insert(QLocale::ClippertonIsland, 953);

    aInfo.insert(270,CurrencyInfo(QObject::tr("Dalasi"),QObject::tr("GMD"),270,QString("D")));
    aCountry.insert(QLocale::Gambia, 270);
    aInfo.insert(981,CurrencyInfo(QObject::tr("Lari"),QObject::tr("GEL"),981,QString(QChar(0x10da))));
    aCountry.insert(QLocale::Georgia, 981);
    aInfo.insert(936,CurrencyInfo(QObject::tr("Ghana Cedi"),QObject::tr("GHS"),936,QChar(0x00a2)));
    aCountry.insert(QLocale::Ghana, 936);
    aInfo.insert(292,CurrencyInfo(QObject::tr("Gibraltar Pound"),QObject::tr("GIP"),292,QChar(0x00a3)));
    aCountry.insert(QLocale::Gibraltar, 292);
    aInfo.insert(320,CurrencyInfo(QObject::tr("Quetzal"),QObject::tr("GTQ"),320,QChar(0x51)));
    aCountry.insert(QLocale::Guatemala, 320);
    aInfo.insert(826,CurrencyInfo(QObject::tr("Pound Sterling"),QObject::tr("GBP"),826,QChar(0x00a3)));
    aCountry.insert(QLocale::Guernsey, 826);
    aCountry.insert(QLocale::IsleOfMan, 826);
    aCountry.insert(QLocale::Jersey, 826);
    aCountry.insert(QLocale::UnitedKingdom, 826);

    aInfo.insert(324,CurrencyInfo(QObject::tr("Guinea Franc"),QObject::tr("GNF"),324,QString("FG")));
    aCountry.insert(QLocale::Guinea, 324);
    aInfo.insert(328,CurrencyInfo(QObject::tr("Guyana Dollar"),QObject::tr("GYD"),328,QChar(0x0024)));
    aCountry.insert(QLocale::Guyana, 328);
    aInfo.insert(332,CurrencyInfo(QObject::tr("Gourde"),QObject::tr("HTG"),332,QString("G")));
    aCountry.insert(QLocale::Haiti, 332);
    //    aCountry.insert(QLocale::Haiti, USD);
    aInfo.insert(340,CurrencyInfo(QObject::tr("Lempira"),QObject::tr("HNL"),340,QString("L")));
    aCountry.insert(QLocale::Honduras, 340);
    aInfo.insert(344,CurrencyInfo(QObject::tr("Hong Kong Dollar"),QObject::tr("HKD"),344,QChar(0x24)));
    aCountry.insert(QLocale::HongKong, 344);
    aInfo.insert(348,CurrencyInfo(QObject::tr("Forint"),QObject::tr("HUF"),348,QString("%1%2").arg(QChar(0x0046)).arg(QChar(0x0074))));
    aCountry.insert(QLocale::Hungary, 348);
    aInfo.insert(352,CurrencyInfo(QObject::tr("Iceland Krona"),QObject::tr("ISK"),352,QString("%1%2").arg(QChar(0x006b)).arg(QChar(0x0072))));
    aCountry.insert(QLocale::Iceland, 352);
    aInfo.insert(356,CurrencyInfo(QObject::tr("Indian Rupee"),QObject::tr("INR"),356,QChar(0x20a8)));
    aCountry.insert(QLocale::India, 356);
    aInfo.insert(360,CurrencyInfo(QObject::tr("Rupiah"),QObject::tr("IDR"),360,QString("%1%2").arg(QChar(0x0052)).arg(QChar(0x0070))));
    aCountry.insert(QLocale::Indonesia, 360);
    aInfo.insert(960,CurrencyInfo(QObject::tr("SDR (Special Drawing Right)"),QObject::tr("XDR"),960,QChar(0x00A4)));
    //aCountry.insert(QLocale::, );
    aInfo.insert(364,CurrencyInfo(QObject::tr("Iranian Rial"),QObject::tr("IRR"),364,QChar(0xfdfc)));
    aCountry.insert(QLocale::Iran, 364);
    aInfo.insert(368,CurrencyInfo(QObject::tr("Iraqi Dinar"),QObject::tr("IQD"),368,QChar(0x00A4)));
    aCountry.insert(QLocale::Iraq, 368);
    aInfo.insert(376,CurrencyInfo(QObject::tr("New Israeli Sheqel"),QObject::tr("ILS"),376,QChar(0x20aa)));
    aCountry.insert(QLocale::Israel, 376);
    aInfo.insert(388,CurrencyInfo(QObject::tr("Jamaican Dollar"),QObject::tr("JMD"),388,QString("%1%2").arg(QChar(0x004a)).arg(QChar(0x0024))));
    aCountry.insert(QLocale::Jamaica, 388);
    aInfo.insert(392,CurrencyInfo(QObject::tr("Yen"),QObject::tr("JPY"),392,QChar(0x00a5)));
    aCountry.insert(QLocale::Japan, 392);
    aInfo.insert(400,CurrencyInfo(QObject::tr("Jordanian Dinar"),QObject::tr("JOD"),400,QString("JD")));
    aCountry.insert(QLocale::Jordan, 400);
    aInfo.insert(398,CurrencyInfo(QObject::tr("Tenge"),QObject::tr("KZT"),398,QChar(0x20b8)));//QString("%1%2").arg(QChar(0x043b)).arg(QChar(0x0432))));
    aCountry.insert(QLocale::Kazakhstan, 398);
    aInfo.insert(404,CurrencyInfo(QObject::tr("Kenyan Shilling"),QObject::tr("KES"),404,QString("KSh")));
    aCountry.insert(QLocale::Kenya, 404);
    aInfo.insert(408,CurrencyInfo(QObject::tr("North Korean Won"),QObject::tr("KPW"),408,QChar(0x20a9)));
    aCountry.insert(QLocale::NorthKorea, 408);
    aInfo.insert(410,CurrencyInfo(QObject::tr("Won"),QObject::tr("KRW"),410,QChar(0x20a9)));
    aCountry.insert(QLocale::SouthKorea, 410);
    aInfo.insert(414,CurrencyInfo(QObject::tr("Kuwaiti Dinar"),QObject::tr("KWD"),414,QString("K.D.")));
    aCountry.insert(QLocale::Kuwait, 414);
    aInfo.insert(417,CurrencyInfo(QObject::tr("Som"),QObject::tr("KGS"),417,QString("%1%2").arg(QChar(0x043b)).arg(QChar(0x0432))));
    aCountry.insert(QLocale::Kyrgyzstan, 417);
    aInfo.insert(418,CurrencyInfo(QObject::tr("Kip"),QObject::tr("LAK"),418,QChar(0x20ad)));
    aCountry.insert(QLocale::Laos, 418);
    aInfo.insert(422,CurrencyInfo(QObject::tr("Lebanese Pound"),QObject::tr("LBP"),422,QChar(0x00a3)));
    aCountry.insert(QLocale::Lebanon, 422);
    aInfo.insert(426,CurrencyInfo(QObject::tr("Loti"),QObject::tr("LSL"),426,QString("M")));
    aCountry.insert(QLocale::Lesotho, 426);
    aInfo.insert(710,CurrencyInfo(QObject::tr("Rand"),QObject::tr("ZAR"),710,QChar(0x0052)));
    //aCountry.insert(QLocale::Lesoth, 710);
    //    aCountry.insert(QLocale::Namibia, 710);
    aCountry.insert(QLocale::SouthAfrica, 710);
    aInfo.insert(430,CurrencyInfo(QObject::tr("Liberian Dollar"),QObject::tr("LRD"),430,QChar(0x0024)));
    aCountry.insert(QLocale::Liberia, 430);
    aInfo.insert(434,CurrencyInfo(QObject::tr("Libyan Dinar"),QObject::tr("LYD"),434,QString("LD")));
    aCountry.insert(QLocale::Libya, 434);
    aInfo.insert(756,CurrencyInfo(QObject::tr("Swiss Franc"),QObject::tr("CHF"),756,QString("%1%2%3").arg(QChar(0x0043)).arg(QChar(0x0048)).arg(QChar(0x0046))));
    aCountry.insert(QLocale::Liechtenstein, 756);
    aInfo.insert(440,CurrencyInfo(QObject::tr("Lithuanian Litas"),QObject::tr("LTL"),440,QString("%1%2").arg(QChar(0x004c)).arg(QChar(0x0074))));
    aCountry.insert(QLocale::Lithuania, 440);
    aInfo.insert(446,CurrencyInfo(QObject::tr("Pataca"),QObject::tr("MOP"),446,QString("MOP$")));
    aCountry.insert(QLocale::Macau, 446);
    aInfo.insert(807,CurrencyInfo(QObject::tr("Denar"),QObject::tr("MKD"),807,QString("%1%2%3").arg(QChar(0x0434)).arg(QChar(0x0435)).arg(QChar(0x043d))));
    aCountry.insert(QLocale::Macedonia, 807);
    aInfo.insert(969,CurrencyInfo(QObject::tr("Malagasy Ariary"),QObject::tr("MGA"),969,QString("Ar")));
    aCountry.insert(QLocale::Madagascar, 969);
    aInfo.insert(454,CurrencyInfo(QObject::tr("Kwacha"),QObject::tr("MWK"),454,QString("MK")));
    aCountry.insert(QLocale::Malawi, 454);
    aInfo.insert(458,CurrencyInfo(QObject::tr("Malaysian Ringgit"),QObject::tr("MYR"),458,QString("%1%2").arg(QChar(0x0052)).arg(QChar(0x004d))));
    aCountry.insert(QLocale::Malaysia, 458);
    aInfo.insert(462,CurrencyInfo(QObject::tr("Rufiyaa"),QObject::tr("MVR"),462,QString("Rf")));
    aCountry.insert(QLocale::Maldives, 462);
    aInfo.insert(478,CurrencyInfo(QObject::tr("Ouguiya"),QObject::tr("MRO"),478,QString("UM")));
    aCountry.insert(QLocale::Mauritania, 478);
    aInfo.insert(480,CurrencyInfo(QObject::tr("Mauritius Rupee"),QObject::tr("MUR"),480,QChar(0x20a8)));
    aCountry.insert(QLocale::Mauritius, 480);
    aInfo.insert(965,CurrencyInfo(QObject::tr("ADB Unit of Account"),QObject::tr("XUA"),965,QChar(0x00A4)));
    //aCountry.insert(QLocale::, ); MEMBER COUNTRIES OF THE AFRICAN DEVELOPMENT BANK GROUP
    aInfo.insert(484,CurrencyInfo(QObject::tr("Mexican Peso"),QObject::tr("MXN"),484,QChar(0x0024)));
    aCountry.insert(QLocale::Mexico, 484);
    aInfo.insert(979,CurrencyInfo(QObject::tr("Mexican Unidad de Inversion (UDI)"),QObject::tr("MXV"),979,QChar(0x00A4)));
    //aCountry.insert(QLocale::Mexico, );
    aInfo.insert(498,CurrencyInfo(QObject::tr("Moldovan Leu"),QObject::tr("MDL"),498,QChar(0x00A4)));
    aCountry.insert(QLocale::Moldova, 498);
    aInfo.insert(496,CurrencyInfo(QObject::tr("Tugrik"),QObject::tr("MNT"),496,QChar(0x20ae)));
    aCountry.insert(QLocale::Mongolia, 496);
    aInfo.insert(504,CurrencyInfo(QObject::tr("Moroccan Dirham"),QObject::tr("MAD"),504,QChar(0x00A4)));
    aCountry.insert(QLocale::Morocco, 504);
    aCountry.insert(QLocale::WesternSahara, 504);
    aInfo.insert(943,CurrencyInfo(QObject::tr("Mozambique Metical"),QObject::tr("MZN"),943,QString("%1%2").arg(QChar(0x004d)).arg(QChar(0x0054))));
    aCountry.insert(QLocale::Mozambique, 943);
    aInfo.insert(104,CurrencyInfo(QObject::tr("Kyat"),QObject::tr("MMK"),104,QString("K")));
    aCountry.insert(QLocale::Myanmar, 104);
    aInfo.insert(516,CurrencyInfo(QObject::tr("Namibia Dollar"),QObject::tr("NAD"),516,QChar(0x0024)));
    aCountry.insert(QLocale::Namibia, 516);
    aInfo.insert(524,CurrencyInfo(QObject::tr("Nepalese Rupee"),QObject::tr("NPR"),524,QChar(0x20a8)));
    aCountry.insert(QLocale::Nepal, 524);
    aInfo.insert(558,CurrencyInfo(QObject::tr("Cordoba Oro"),QObject::tr("NIO"),558,QString("%1%2").arg(QChar(0x0043)).arg(QChar(0x0024))));
    aCountry.insert(QLocale::Nicaragua, 558);
    aInfo.insert(566,CurrencyInfo(QObject::tr("Naira"),QObject::tr("NGN"),566,QChar(0x20a6)));
    aCountry.insert(QLocale::Nigeria, 566);
    aInfo.insert(512,CurrencyInfo(QObject::tr("Rial Omani"),QObject::tr("OMR"),512,QChar(0xfdfc)));
    aCountry.insert(QLocale::Oman, 512);
    aInfo.insert(586,CurrencyInfo(QObject::tr("Pakistan Rupee"),QObject::tr("PKR"),586,QChar(0x20a8)));
    aCountry.insert(QLocale::Pakistan, 586);
    aInfo.insert(590,CurrencyInfo(QObject::tr("Balboa"),QObject::tr("PAB"),590,QString("%1%2%3").arg(QChar(0x0042)).arg(QChar(0x002f)).arg(QChar(0x002e))));
    aCountry.insert(QLocale::Panama, 590);
    aInfo.insert(598,CurrencyInfo(QObject::tr("Kina"),QObject::tr("PGK"),598,QString("K")));
    aCountry.insert(QLocale::PapuaNewGuinea, 598);
    aInfo.insert(600,CurrencyInfo(QObject::tr("Guarani"),QObject::tr("PYG"),600,QString("%1%2").arg(QChar(0x0047)).arg(QChar(0x0073))));
    aCountry.insert(QLocale::Paraguay, 600);
    aInfo.insert(604,CurrencyInfo(QObject::tr("Nuevo Sol"),QObject::tr("PEN"),604,QString("%1%2%3").arg(QChar(0x0053)).arg(QChar(0x002f)).arg(QChar(0x002e))));
    aCountry.insert(QLocale::Peru, 604);
    aInfo.insert(608,CurrencyInfo(QObject::tr("Philippine Peso"),QObject::tr("PHP"),608,QChar(0x20b1)));
    aCountry.insert(QLocale::Philippines, 608);
    aInfo.insert(985,CurrencyInfo(QObject::tr("Zloty"),QObject::tr("PLN"),985,QString("%1%2").arg(QChar(0x007a)).arg(QChar(0x0142))));
    aCountry.insert(QLocale::Poland, 985);
    aInfo.insert(634,CurrencyInfo(QObject::tr("Qatari Rial"),QObject::tr("QAR"),634,QChar(0xfdfc)));
    aCountry.insert(QLocale::Qatar, 634);
    aInfo.insert(946,CurrencyInfo(QObject::tr("New Romanian Leu"),QObject::tr("RON"),946,QString("leu")));
    aCountry.insert(QLocale::Romania, 946);
    aInfo.insert(643,CurrencyInfo(QObject::tr("Russian Ruble"),QObject::tr("RUB"),643,QString("%1%2%3").arg(QChar(0x0440)).arg(QChar(0x0443)).arg(QChar(0x0431))));
    aCountry.insert(QLocale::RussianFederation, 643);
    aInfo.insert(646,CurrencyInfo(QObject::tr("Rwanda Franc"),QObject::tr("RWF"),646,QString("FRw")));
    aCountry.insert(QLocale::Rwanda, 646);
    aInfo.insert(654,CurrencyInfo(QObject::tr("Saint Helena Pound"),QObject::tr("SHP"),654,QChar(0xa3)));
    aCountry.insert(QLocale::SaintHelena, 654);
    aInfo.insert(882,CurrencyInfo(QObject::tr("Tala"),QObject::tr("WST"),882,QString("WS$")));
    aCountry.insert(QLocale::Samoa, 882);
    aInfo.insert(678,CurrencyInfo(QObject::tr("Dobra"),QObject::tr("STD"),678,QString("Db")));
    aCountry.insert(QLocale::SaoTomeAndPrincipe, 678);
    aInfo.insert(682,CurrencyInfo(QObject::tr("Saudi Riyal"),QObject::tr("SAR"),682,QChar(0xfdfc)));
    aCountry.insert(QLocale::SaudiArabia, 682);
    aInfo.insert(941,CurrencyInfo(QObject::tr("Serbian Dinar"),QObject::tr("RSD"),941,QString("%1%2%3%4").arg(QChar(0x0441)).arg(QChar(0x0438)).arg(QChar(0x043d)).arg(QChar(0x002e))));
    aCountry.insert(QLocale::Serbia, 941);
    aInfo.insert(690,CurrencyInfo(QObject::tr("Seychelles Rupee"),QObject::tr("SCR"),690,QChar(0x20a8)));
    aCountry.insert(QLocale::Seychelles, 690);
    aInfo.insert(694,CurrencyInfo(QObject::tr("Leone"),QObject::tr("SLL"),694,QString("Le")));
    aCountry.insert(QLocale::SierraLeone, 694);
    aInfo.insert(702,CurrencyInfo(QObject::tr("Singapore Dollar"),QObject::tr("SGD"),702,QChar(0x24)));
    aCountry.insert(QLocale::Singapore, 702);
    aInfo.insert(994,CurrencyInfo(QObject::tr("Sucre"),QObject::tr("XSU"),994,QChar(0x00A4)));
    //aCountry.insert(QLocale::, ); SISTEMA UNITARIO DE COMPENSACION REGIONAL DE PAGOS "SUCRE"
    aInfo.insert(90,CurrencyInfo(QObject::tr("Solomon Islands Dollar"),QObject::tr("SBD"),90,QChar(0x0024)));
    aCountry.insert(QLocale::SolomonIslands, 90);
    aInfo.insert(706,CurrencyInfo(QObject::tr("Somali Shilling"),QObject::tr("SOS"),706,QChar(0x0053)));
    aCountry.insert(QLocale::Somalia, 706);
    aInfo.insert(728,CurrencyInfo(QObject::tr("South Sudanese Pound"),QObject::tr("SSP"),728,QChar(0x00A4)));
    aCountry.insert(QLocale::SouthSudan, 728);
    aInfo.insert(144,CurrencyInfo(QObject::tr("Sri Lanka Rupee"),QObject::tr("LKR"),144,QChar(0x20a8)));
    aCountry.insert(QLocale::SriLanka, 144);
    aInfo.insert(938,CurrencyInfo(QObject::tr("Sudanese Pound"),QObject::tr("SDG"),938,QChar(0x00A4)));
    aCountry.insert(QLocale::Sudan, 938);
    aInfo.insert(968,CurrencyInfo(QObject::tr("Surinam Dollar"),QObject::tr("SRD"),968,QChar(0x0024)));
    aCountry.insert(QLocale::Suriname, 968);
    aInfo.insert(748,CurrencyInfo(QObject::tr("Lilangeni"),QObject::tr("SZL"),748,QString("E")));
    aCountry.insert(QLocale::Swaziland, 748);
    aInfo.insert(752,CurrencyInfo(QObject::tr("Swedish Krona"),QObject::tr("SEK"),752,QString("%1%2").arg(QChar(0x006b)).arg(QChar(0x0072))));
    aCountry.insert(QLocale::Sweden, 752);
    aInfo.insert(947,CurrencyInfo(QObject::tr("WIR Euro"),QObject::tr("CHE"),947,QChar(0x00A4)));
    //aCountry.insert(QLocale::Switzerland, );
    aInfo.insert(756,CurrencyInfo(QObject::tr("Swiss Franc"),QObject::tr("CHF"),756,QString("%1%2%3").arg(QChar(0x0043)).arg(QChar(0x0048)).arg(QChar(0x0046))));
    aCountry.insert(QLocale::Switzerland, 756);
    aInfo.insert(948,CurrencyInfo(QObject::tr("WIR Franc"),QObject::tr("CHW"),948,QChar(0x00A4)));
    //    aCountry.insert(QLocale::Switzerland, );
    aInfo.insert(760,CurrencyInfo(QObject::tr("Syrian Pound"),QObject::tr("SYP"),760,QChar(0x00a3)));
    aCountry.insert(QLocale::SyrianArabRepublic, 760);
    aInfo.insert(901,CurrencyInfo(QObject::tr("New Taiwan Dollar"),QObject::tr("TWD"),901,QString("%1%2%3").arg(QChar(0x004e)).arg(QChar(0x0054)).arg(QChar(0x0024))));
    aCountry.insert(QLocale::Taiwan, 901);
    aInfo.insert(972,CurrencyInfo(QObject::tr("Somoni"),QObject::tr("TJS"),972,QChar(0x00A4)));
    aCountry.insert(QLocale::Tajikistan, 972);
    aInfo.insert(834,CurrencyInfo(QObject::tr("Tanzanian Shilling"),QObject::tr("TZS"),834,QChar(0x00A4)));
    aCountry.insert(QLocale::Tanzania, 834);
    aInfo.insert(764,CurrencyInfo(QObject::tr("Baht"),QObject::tr("THB"),764,QChar(0x0e3f)));
    aCountry.insert(QLocale::Thailand, 764);
    aInfo.insert(776,CurrencyInfo(QObject::tr("Pa’anga"),QObject::tr("TOP"),776,QChar(0x00A4)));
    aCountry.insert(QLocale::Tonga, 776);
    aInfo.insert(780,CurrencyInfo(QObject::tr("Trinidad and Tobago Dollar"),QObject::tr("TTD"),780,QString("%1%2%3").arg(QChar(0x0054)).arg(QChar(0x0054)).arg(QChar(0x0024))));
    aCountry.insert(QLocale::TrinidadAndTobago, 780);
    aInfo.insert(788,CurrencyInfo(QObject::tr("Tunisian Dinar"),QObject::tr("TND"),788,QChar(0x00A4)));
    aCountry.insert(QLocale::Tunisia, 788);
    aInfo.insert(949,CurrencyInfo(QObject::tr("Turkish Lira"),QObject::tr("TRY"),949,QChar(0x20ba)));
    aCountry.insert(QLocale::Turkey, 949);
    aInfo.insert(934,CurrencyInfo(QObject::tr("Turkmenistan New Manat"),QObject::tr("TMT"),934,QChar(0x20bc)));
    aCountry.insert(QLocale::Turkmenistan, 934);
    aInfo.insert(800,CurrencyInfo(QObject::tr("Uganda Shilling"),QObject::tr("UGX"),800,QString("USh")));
    aCountry.insert(QLocale::Uganda, 800);
    aInfo.insert(980,CurrencyInfo(QObject::tr("Hryvnia"),QObject::tr("UAH"),980,QChar(0x20b4)));
    aCountry.insert(QLocale::Ukraine, 980);
    aInfo.insert(784,CurrencyInfo(QObject::tr("UAE Dirham"),QObject::tr("AED"),784,QChar(0x00A4)));
    aCountry.insert(QLocale::UnitedArabEmirates, 784);
    aInfo.insert(997,CurrencyInfo(QObject::tr("US Dollar (Next day)"),QObject::tr("USN"),997,QChar(0x0024)));
    //aCountry.insert(QLocale::UnitedStates, );
    aInfo.insert(940,CurrencyInfo(QObject::tr("Uruguay Peso en Unidades Indexadas (URUIURUI)"),QObject::tr("UYI"),940,QChar(0x00A4)));
    //aCountry.insert(QLocale::Uruguay, );
    aInfo.insert(858,CurrencyInfo(QObject::tr("Peso Uruguayo"),QObject::tr("UYU"),858,QString("%1%2").arg(QChar(0x0024)).arg(QChar(0x0055))));
    aCountry.insert(QLocale::Uruguay, 858);
    aInfo.insert(860,CurrencyInfo(QObject::tr("Uzbekistan Som"),QObject::tr("UZS"),860,QString("som")));
    aCountry.insert(QLocale::Uzbekistan, 860);
    aInfo.insert(548,CurrencyInfo(QObject::tr("Vatu"),QObject::tr("VUV"),548,QString("VT")));
    aCountry.insert(QLocale::Vanuatu, 548);
    aInfo.insert(937,CurrencyInfo(QObject::tr("Bolivar"),QObject::tr("VEF"),937,QString("%1%2").arg(QChar(0x0042)).arg(QChar(0x0073))));
    aCountry.insert(QLocale::Venezuela, 937);
    aInfo.insert(704,CurrencyInfo(QObject::tr("Dong"),QObject::tr("VND"),704,QChar(0x20ab)));
    aCountry.insert(QLocale::Vietnam, 704);
    aInfo.insert(886,CurrencyInfo(QObject::tr("Yemeni Rial"),QObject::tr("YER"),886,QChar(0xfdfc)));
    aCountry.insert(QLocale::Yemen, 886);
    aInfo.insert(967,CurrencyInfo(QObject::tr("Zambian Kwacha"),QObject::tr("ZMW"),967,QString("ZK")));
    aCountry.insert(QLocale::Zambia, 967);
    aInfo.insert(932,CurrencyInfo(QObject::tr("Zimbabwe Dollar"),QObject::tr("ZWL"),932,QString("%1%2").arg(QChar(0x005a)).arg(QChar(0x0024))));
    aCountry.insert(QLocale::Zimbabwe, 932);
    aInfo.insert(955,CurrencyInfo(QObject::tr("Bond Markets Unit European Composite Unit (EURCO)"),QObject::tr("XBA"),955,QChar(0x00A4)));
    aInfo.insert(956,CurrencyInfo(QObject::tr("Bond Markets Unit European Monetary Unit (E.M.U.-6)"),QObject::tr("XBB"),956,QChar(0x00A4)));
    aInfo.insert(957,CurrencyInfo(QObject::tr("Bond Markets Unit European Unit of Account 9 (E.U.A.-9)"),QObject::tr("XBC"),957,QChar(0x00A4)));
    aInfo.insert(958,CurrencyInfo(QObject::tr("Bond Markets Unit European Unit of Account 17 (E.U.A.-17)"),QObject::tr("XBD"),958,QChar(0x00A4)));
    aInfo.insert(999,CurrencyInfo(QObject::tr("The codes assigned for transactions where no currency is involved"),QObject::tr("XXX"),999,QString(QChar(0x00A4))));
    aInfo.insert(959,CurrencyInfo(QObject::tr("Gold"),QObject::tr("XAU"),959,QChar(0x00A4)));
    aInfo.insert(964,CurrencyInfo(QObject::tr("Palladium"),QObject::tr("XPD"),964,QChar(0x00A4)));
    aInfo.insert(962,CurrencyInfo(QObject::tr("Platinum"),QObject::tr("XPT"),962,QChar(0x00A4)));
    aInfo.insert(961,CurrencyInfo(QObject::tr("Silver"),QObject::tr("XAG"),961,QChar(0x00A4)));
}
