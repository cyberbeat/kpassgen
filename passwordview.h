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
#ifndef PASSWORDLIST_H
#define PASSWORDLIST_H

#include <QTableView>

class QMouseEvent;
class QPoint;

class PasswordView : public QTableView
{
Q_OBJECT
public:
    PasswordView(QWidget *parent = 0);

public slots:
    void copyCurrentItem();
    void setMonoFont(bool b = false);

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void preformDrag();
    QString currentPassword();

    QPoint dragStartPos;
};

#endif // PASSWORDLIST_H
