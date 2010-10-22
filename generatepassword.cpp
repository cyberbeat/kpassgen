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
const QString amb("B8G6I1l0OQDS5Z");

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

QStringList GeneratePassword::genPernouncable(int length, int amount, QFlags<Option> &flags)
{
    QStringList passlist;
    bool number     = flags & Number;
    bool upper      = flags & Upper;
    bool unambigous = flags & Unambiguous;
    
    kDebug() << "Unambiguous: " << unambigous;

    for(int c = 0; c < amount; c++)
    {
        QString password;
        int cvwl = 0, ccon = 0; //Counts for vowel and constinate
        QList<int> digitsList;
        QList<int> upperList;

        // Pick number count and positions
        if (number) {
            int numdidgets = Random::nextUInt(1, qMax(length/6, 1));
            for (int i = 0; i < numdidgets; i++) {
                digitsList.append(Random::nextUInt(length));
            }
        }
        
        // Pick upper count and positions
        if (upper) {
            int numupper = Random::nextUInt(1, qMax(length/6, 1));
            for (int i = 0; i < numupper; i++) {
                int num = 0;
                do {
                    num = Random::nextUInt(length);
                } while(digitsList.contains(num));
                upperList.append(num);
            }
        }
        
        // Generate the password
        for(int i=0; i<length; i++) {
            bool ulist = upperList.contains(i);
            // if number pick number
            if (digitsList.contains(i)) {
                password.append(getChar(num, false, unambigous));
                ccon = 0;
                cvwl = 0;
            }
            // else if cvwl > 1 pick const; reset counters
            else if (cvwl > 0) {
                password.append(getChar(con, ulist, unambigous));
                ccon = 1;
                cvwl = 0;
            }
            // else if ccon > 1 pick vowel; reset counters
            else if (ccon > 1) {
                password.append(getChar(vwl, ulist, unambigous));
                ccon = 0;
                cvwl = 1;
            }
            // else pick random letter or vowel
            else {
                if (Random::nextUInt(2)) {
                    password.append(getChar(vwl, ulist, unambigous));
                    ccon++;
                 } else {
                    password.append(getChar(con, ulist, unambigous));
                    cvwl++;
                }
            }
        } /* end of password */

        passlist.append(password);
    } /* end of password group */


    return passlist;
}


QChar GeneratePassword::getChar(const QString &list, bool upper, bool unambigous)
{
    QString charlist = list;
    QChar picked;
    do {
        picked = charlist.at(Random::nextUInt(charlist.length()));
        if (upper) {
            picked = picked.toUpper();
        }
    } while (amb.contains(picked));
    return picked;
}