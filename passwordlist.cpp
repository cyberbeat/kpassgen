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
#include "passwordlist.h"
#include "passwordwidget.h"

#include <QApplication>
#include <QMouseEvent>
#include <QLabel>
#include <QFont>
#include <QClipboard>
#include <QProgressBar>

PasswordList::PasswordList(QWidget *parent) : KListWidget(parent)
{
	setAutoScroll(true);
	setDragEnabled(true);
	setContextMenuPolicy(Qt::ActionsContextMenu);
}

void PasswordList::replace(QStringList &passlist)
{
    clear();
    for( int i = 0; i < passlist.length(); i++) {
        addItem(passlist.at(i));
        QListWidgetItem *m = item(i);
        setItemWidget(m, new PasswordWidget(m->text()));
    }
}

void PasswordList::copy(int index)
{
    // Get an index of the current items if index is -1 or to large
    if (index < 0 || index >= count()) {
        if (currentRow() < 0)
            setCurrentRow(0);
        index = currentRow();
    } else {// otherwise select that item
        setCurrentRow(index);
    }

    QString password = currentItem()->text();

    QClipboard *cb = QApplication::clipboard();

    cb->setText(password, QClipboard::Clipboard);
}

void PasswordList::setMonoFont(bool b)
{
    QFont font;
    if (b) {
        font = QFont("Courier");
    }
    setFont(font);
}

void PasswordList::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
		dragStartPos = event->pos();
	QListWidget::mousePressEvent(event);
}


void PasswordList::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) {
		int distance = (event->pos() - dragStartPos).manhattanLength();
		if (distance >= QApplication::startDragDistance())
			preformDrag();
	}
//	QListWidget::mouseMoveEvent(event);
}

void PasswordList::preformDrag()
{
	QListWidgetItem *item = currentItem();
	if (item) {
		QMimeData *mimeData = new QMimeData;
		mimeData->setText(item->text());

		QLabel label(item->text());
		label.resize(label.sizeHint());
		QPixmap pixmap(label.size());
		label.render(&pixmap);

		QDrag *drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->setPixmap(pixmap);
		drag->exec();
	}
}
