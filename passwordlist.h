#ifndef PASSWORDLIST_H
#define PASSWORDLIST_H

#include <KListWidget>

class QMouseEvent;
class QPoint;

class PasswordList : public KListWidget
{
public:
	PasswordList(QWidget *parent = 0);

	void replace(QStringList &passlist);

private:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void preformDrag();

	QPoint dragStartPos;
};

#endif // PASSWORDLIST_H
