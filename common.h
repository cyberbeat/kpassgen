/*
    Copyright 2011 Michael Daffin <james1479@googlemail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2 as
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef COMMON_H
#define COMMON_H

#include <KLocalizedString>

const QString lowercase_set(i18n("abcdefghijklmnopqrstuvwxyz"));
const QString uppercase_set(i18n("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
const QString symbol_set(i18n("¬`!\"£$%^&*()_+-={}[];'#:@~<>?,./|\\ "));
const QString number_set(i18n("0123456789"));
const QString hex_set(i18n("0123456789ABCDEF"));
const QString consonant_set(i18n("bcdfghjklmnpqrstvwxz"));
const QString vowel_set(i18n("aeiouy"));
const QString ambiguous_set(i18n("B8G6I1l0OQDS5Z2"));

#endif // COMMON_H
