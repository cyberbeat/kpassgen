#include "passwordwidget.h"
#include "common.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QPainter>

PasswordWidget::PasswordWidget ( QObject *parent ) :
        QItemDelegate ( parent ) { }

void PasswordWidget::paint ( QPainter* painter, 
                             const QStyleOptionViewItem& option, 
                             const QModelIndex& index ) const
{
    if (!index.isValid()) return;
    if (index.column() == 0) {
        QItemDelegate::paint(painter, option, index);
        return;
    }
    
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }

    int progress = index.data(Qt::DisplayRole).toInt();
    // Draws the progress bar
    QStyleOptionProgressBar bar;
    QRect rect = option.rect;
    QRect newrect(rect.left(), rect.top() + rect.height()/2 -10, rect.width(), 20);
    bar.rect = newrect;

    bar.state = QStyle::State_Enabled;
    bar.direction = QApplication::layoutDirection();
    //bar.rect = option.rect;
    bar.fontMetrics = QApplication::fontMetrics();
    bar.minimum = 0;
    bar.maximum = 100;
    bar.progress = progress;
    bar.textVisible = false;
    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &bar, painter, 0);

}
