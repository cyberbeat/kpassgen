/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef PASSWORDMODEL_H
#define PASSWORDMODEL_H

#include <qabstractitemmodel.h>

#include <QStringList>;


class PasswordModel : public QAbstractTableModel
{

public:
    virtual QVariant data ( const QModelIndex& index, int role = Qt::DisplayRole ) const;
    virtual int columnCount ( const QModelIndex& parent = QModelIndex() ) const;
    virtual int rowCount ( const QModelIndex& parent = QModelIndex() ) const;
    virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    virtual Qt::ItemFlags flags ( const QModelIndex& index ) const;
    virtual void sort ( int column, Qt::SortOrder order = Qt::AscendingOrder );
    PasswordModel();
    PasswordModel ( const PasswordModel& other );
    virtual ~PasswordModel();
    
public slots:
    void addPassword(const QString &password);
    void clear();
    
private:
    QStringList passwords;
};

#endif // PASSWORDMODEL_H
