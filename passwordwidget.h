#ifndef STRENGTHBAR_H
#define STRENGTHBAR_H

#include <QItemDelegate>
#include <QProgressBar>
#include <QLabel>

class PasswordWidget : public QItemDelegate
{
    Q_OBJECT
public:
    explicit PasswordWidget(QObject *parent = 0);
    void paint(QPainter* painter, const QStyleOptionViewItem& option,
                        const QModelIndex& index) const;
};

#endif // STRENGTHBAR_H
