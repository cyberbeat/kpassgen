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

#include <KDebug>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/times.h>
#include <argp.h>

const QString con("bcdfghjklmnpqrstvwxz");
const QString vwl("aeiouy");
const QString num("0123456789");

QStringList GeneratePassword::genRandom(int length, QString &characterset,
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
            // Pick a random character
            int index = Random::nextInt(cs.length());
            password.append(cs[index]);
            // Remove chosen character if Unique flag passed
            if (flags & Unique) {
                cs.remove(index, 1);
            }
        }
        passwordList.append(password);
    }

    return passwordList;
}

QStringList GeneratePassword::genPernouncable(int length, int amount)
{
    QStringList passlist;

    for(int c = 0; c < amount; c++)
    {
        QString password;
        int cvwl, ccon; //Counts for vowel and constinate
        QList<int> digits;

        // Pick number count and positions
        {
            int numdidgets = Random::nextUInt(1, qMax(length/6, 1));
            for (int i = 0; i < numdidgets; i++) {
                digits.append(Random::nextUInt(length));
            }
        }

        for(int i=0; i<length; i++) {
            // if number pick number
            if (digits.contains(i)) {
                password.append(num.at(Random::nextUInt(num.length())));
            }
            // else if cvwl > 1 pick const; reset counters
            else if (cvwl > 0) {
                password.append(con.at(Random::nextUInt(con.length())));
                ccon = 1;
                cvwl = 0;
            }
            // else if ccon > 1 pick vowel; reset counters
            else if (ccon > 1) {
                password.append(vwl.at(Random::nextUInt(vwl.length())));
                ccon = 0;
                cvwl = 1;
            }
            // else pick random letter or vowel
            else {
                if (Random::nextUInt(2)) {
                    password.append(con.at(Random::nextUInt(con.length())));
                    ccon++;
                 } else {
                    password.append(vwl.at(Random::nextUInt(vwl.length())));
                    cvwl++;
                }
            }
        } /* end of password */

        // pick random letters to captilise
        passlist.append(password);
    } /* end of password group */


    return passlist;
}
