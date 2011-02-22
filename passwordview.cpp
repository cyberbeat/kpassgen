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
#include "passwordview.h"
#include "passwordwidget.h"
#include "passwordmodel.h"

#include <QApplication>
#include <QMouseEvent>
#include <QLabel>
#include <QFont>
#include <QClipboard>
#include <QProgressBar>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDebug>

PasswordView::PasswordView ( QWidget *parent ) : QTableView ( parent )
{
    setAutoScroll ( true );
    setDragEnabled ( true );
    setItemDelegate(new PasswordWidget(this));
    setAlternatingRowColors ( true );
    setContextMenuPolicy ( Qt::ActionsContextMenu );
}

void PasswordView::copyCurrentItem()
{
    // Get an index of the current items if index is -1 or to large
    if (!currentIndex().isValid()) {
        qDebug() << "Failed to copy: Index not valid";
        return;
    }
    
    QString password = model()->data(currentIndex()).toString();

    QClipboard *cb = QApplication::clipboard();

    cb->setText ( password, QClipboard::Clipboard );
}

void PasswordView::setMonoFont ( bool b )
{
    QFont font;
    if ( b )
    {
        font.setFamily ( "Monospace" );
        font.setStyleHint ( QFont::TypeWriter );
    }
    setFont ( font );
}

void PasswordView::mousePressEvent ( QMouseEvent *event )
{
    if ( event->button() == Qt::LeftButton )
        dragStartPos = event->pos();
    QTableView::mousePressEvent ( event );
}


void PasswordView::mouseMoveEvent ( QMouseEvent *event )
{
    if ( event->buttons() & Qt::LeftButton )
    {
        int distance = ( event->pos() - dragStartPos ).manhattanLength();
        if ( distance >= QApplication::startDragDistance() )
            preformDrag();
    }
//  QListWidget::mouseMoveEvent(event);
}

void PasswordView::preformDrag()
{
    /*
    QListWidgetItem *item = current
    if ( item )
    {
        QString pass = item->text();
        QMimeData *mimeData = new QMimeData;
        mimeData->setText ( pass );

        if ( pass.length() > 26 )
        {
            pass.truncate ( 23 );
            pass.append ( "..." );
        }
        QLabel label ( pass );
        label.resize ( label.sizeHint() );
        QPixmap pixmap ( label.size() );
        label.render ( &pixmap );

        QDrag *drag = new QDrag ( this );
        drag->setMimeData ( mimeData );
        drag->setPixmap ( pixmap );
        drag->exec();
    }
    */
}
