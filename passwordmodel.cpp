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
#include "common.h"
#include <KDebug>

PasswordModel::PasswordModel( QObject* parent ): QAbstractTableModel(parent),
    reasonablePasswordLength(12)
{
}

PasswordModel::PasswordModel( const PasswordModel& other ) : 
    QAbstractTableModel(other),
    reasonablePasswordLength(12) 
{
}

PasswordModel::~PasswordModel()
{
}

QVariant PasswordModel::data ( const QModelIndex& index, int role ) const
{
    if (!index.isValid())
        return QVariant();

    if ( role == Qt::DisplayRole ) {
        int row = index.row();
        int column = index.column();

        if (column == 0)
            return passwords.at(row);
        else if (column == 1)
            return QVariant(100);
    }
    return QVariant();
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
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return QVariant();
    if (section < 0 || section >= columnCount()) return QVariant();
    
    switch(section) {
        case 0: return QVariant("Password");
        case 1: return QVariant("Strength");
    }
    return QVariant();
}

Qt::ItemFlags PasswordModel::flags ( const QModelIndex& index ) const
{
    return QAbstractItemModel::flags ( index );
}

void PasswordModel::sort ( int column, Qt::SortOrder order )
{
    QAbstractItemModel::sort ( column, order );
}

void PasswordModel::addPassword ( const QString& password )
{
    int row = passwords.length();
    beginInsertRows(QModelIndex(), row, row);
    passwords.append(password);
    endInsertRows();
}

void PasswordModel::clear()
{ 
    beginRemoveRows(QModelIndex(), 0, passwords.count() - 1);
    passwords.clear(); 
    endRemoveRows();
}

int PasswordModel::getStrength ( const QString &password ) const
{
    // Password strength calculator borrowed from kwallet.cpp
    int pwstrength = ( 20 * password.length() + 80 * effectivePasswordLength ( password ) ) / qMax ( reasonablePasswordLength, 2 );
    if ( pwstrength < 0 )
    {
        pwstrength = 0;
    }
    else if ( pwstrength > 100 )
    {
        pwstrength = 100;
    }
    return pwstrength;
}

// Borrowed from kwallet.cpp :)
int PasswordModel::effectivePasswordLength ( const QString &password ) const
{
    enum Category
    {
        Digit,
        Upper,
        Vowel,
        Consonant,
        Special
    };

    Category previousCategory = Vowel;
    int count = 0;

    for ( int i = 0; i < password.length(); ++i )
    {
        QChar currentChar = password.at ( i );
        if ( !password.left ( i ).contains ( currentChar ) )
        {
            Category currentCategory;
            switch ( currentChar.category() )
            {
            case QChar::Letter_Uppercase:
                currentCategory = Upper;
                break;
            case QChar::Letter_Lowercase:
                if ( vowel_set.contains ( currentChar ) )
                {
                    currentCategory = Vowel;
                }
                else
                {
                    currentCategory = Consonant;
                }
                break;
            case QChar::Number_DecimalDigit:
                currentCategory = Digit;
                break;
            default:
                currentCategory = Special;
                break;
            }
            switch ( currentCategory )
            {
            case Vowel:
                if ( previousCategory != Consonant )
                {
                    ++count;
                }
                break;
            case Consonant:
                if ( previousCategory != Vowel )
                {
                    ++count;
                }
                break;
            default:
                if ( previousCategory != currentCategory )
                {
                    ++count;
                }
                break;
            }
            previousCategory = currentCategory;
        }
    }
    return count;
}
