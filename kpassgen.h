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

namespace Ui {
    class KPassGen;
}

class KPassGen : public QWidget
{
    Q_OBJECT

public:
    explicit KPassGen(QWidget *parent = 0);
    ~KPassGen();

    void writeSettings();
    void readSettings();

private slots:
    void genPass();
    void pageIndexChanged(int index);
    void alphaUpdate();
    void uniqueToggle(bool unique);
    void copy(int index = -1);
    void clear();
    void setMonoFont(bool b = false);
    void setCopyEnabled(bool b = true);

signals:
    void passwordsChanged();
    void passwordsCleared();

protected:
    void changeEvent(QEvent *e);

private:
    QString getCharacterSet();
    Ui::KPassGen *ui;
};

const QString ambiguous = "B8G6I1l0OQDS5Z2";

#endif // KPASSGEN_H
