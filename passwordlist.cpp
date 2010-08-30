#include "passwordlist.h"

#include <QApplication>
#include <QMouseEvent>
#include <QFont>

PasswordList::PasswordList(QWidget *parent) : KListWidget(parent)
{
	setAutoScroll(true);
	setDragEnabled(true);
	setContextMenuPolicy(Qt::ActionsContextMenu);
//	QFont font("Courier");
//	setFont(font);
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
#include <QLabel>
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
