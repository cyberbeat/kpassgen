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
#ifndef RANDOM_H
#define RANDOM_H
#include <limits>
#include <time.h>
#include <QtGlobal>

class Random
{
public:
    static void init()         { qsrand(time(NULL)); }
    static void init(int seed) { qsrand(seed); }

    static int nextInt() { return qrand(); }
    static int nextInt(int max) { return qrand() % max; }
    static int nextInt(int min, int max) { return ((int) qrand() % max) + min; }

    static unsigned int nextUInt() { return qrand(); }
    static unsigned int nextUInt(int max) { return qrand() % max; }
    static unsigned int nextUInt(int min, int max) { return (qrand() % max) + min; }

private:
    Random() {}
};

#endif // RANDOM_H
