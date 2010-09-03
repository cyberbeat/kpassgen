/*
	Copyright 2009 Michael Daffin <james1479@googlemail.com>

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "generatepassword.h"
#include "settings.h"
#include "random.h"

QStringList GeneratePassword::genAlphanumerical(int length, QString &characterset,
                                       int amount, QFlags<Option> &flags)
{
    QStringList passwordList;

    if (length > characterset.length() && flags & Unique) {
        kError() << "Length greater then characterset length, "
                    "cannot generate unique passwords";
        return QStringList();
    }

    while (passwordList.length() < amount) {
        QString password;
        QString cs = characterset;

        while (password.length() < length) {
            int index = Random::nextInt(cs.length());
            password.append(cs[index]);
            if (flags & Unique) {
                cs.remove(index, 1);
            }
        }
        passwordList.append(password);
    }

    return passwordList;
}

