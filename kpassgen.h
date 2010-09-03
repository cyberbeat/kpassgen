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
#ifndef KPASSGEN_H
#define KPASSGEN_H

#include <QWidget>
#include "ui_kpassgen.h"

//namespace Ui {
//    class KPassGen;
//}

class KPassGen : public QWidget
{
    Q_OBJECT

public:
    explicit KPassGen(QWidget *parent = 0);
    ~KPassGen();

    bool writeSettings();
    bool readSettings();

private slots:
    void genPass();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::KPassGen *ui;
};

#endif // KPASSGEN_H