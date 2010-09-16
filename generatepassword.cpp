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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/times.h>
#include <argp.h>

#define NC_(array)	( sizeof(array) / sizeof(array[0]) )
#define F_(i)		( (float) (i) )

#define MAX_PW_LENGTH		64
#define MIN_PW_LENGTH		4
#define DEFAULT_PW_LENGTH	8
#define MAX_GROUP		100
#define MIN_GROUP		1
#define DEFAULT_GROUP		1

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

QStringList GeneratePassword::genPernouncable(int length, int amount)
{
    int len, grp, digit;
    QStringList passlist;

    grp = amount;

    if(length > MIN_PW_LENGTH)
    {
        if(length < MAX_PW_LENGTH)
        len = length;
        else
            len = MAX_PW_LENGTH;
    }
    else
    {
        len = MIN_PW_LENGTH;
    }

    if(amount > MIN_GROUP)
    {
        if(amount < MAX_GROUP)
        grp = amount;
        else
            grp = MAX_GROUP;
    }
    else
    {
        grp = MIN_GROUP;
    }

    for(int c=0; c<grp; c++)
    {
        digit=(int) (((float) (len))*rand()/(RAND_MAX+1.0));
        QString password;

        for(int i=0; i<len; i++) {
            if(i==digit) {
                password.append(num.at(Random::nextUInt(num.length())));
            }
            else if( i%2 ) {
                password.append(vwl.at(Random::nextUInt(vwl.length())));
            }
            else {
                password.append(con.at(Random::nextUInt(con.length())));
            }

        } /* end of password */

        passlist.append(password);
    } /* end of group */


    return passlist;
}
