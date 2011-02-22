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


#include "passwordmodel.h"

QVariant PasswordModel::data ( const QModelIndex& index, int role ) const
{
    if (!index.isValid())
        return QVariant();
    
    return 1;
}

int PasswordModel::columnCount ( const QModelIndex& parent ) const
{
    return 2;
}

int PasswordModel::rowCount ( const QModelIndex& parent ) const
{
    return passwords.count();
}

QVariant PasswordModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    return QAbstractItemModel::headerData ( section, orientation, role );
}

Qt::ItemFlags PasswordModel::flags ( const QModelIndex& index ) const
{
    return QAbstractItemModel::flags ( index );
}

void PasswordModel::sort ( int column, Qt::SortOrder order )
{
    QAbstractItemModel::sort ( column, order );
}

PasswordModel::PasswordModel()
{

}

PasswordModel::PasswordModel ( const PasswordModel& other )
{

}

PasswordModel::~PasswordModel()
{
    
}


