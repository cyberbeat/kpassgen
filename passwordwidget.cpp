#include "passwordwidget.h"
#include "common.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QPainter>

PasswordWidget::PasswordWidget(QObject *parent) :
    QItemDelegate(parent), reasonablePasswordLength(12) { }

void PasswordWidget::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QItemDelegate::paint(painter, option, index);

    int progress = getStrength(index.data(Qt::DisplayRole).toString());
    // Draws teh progress bar
    QStyleOptionProgressBar bar;
    QRect rect = option.rect;
    rect.setLeft(rect.right() - 100);
    bar.rect = rect;
    bar.minimum = 0;
    bar.maximum = 100;
    bar.progress = progress;
    bar.textVisible = false;
    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &bar, painter, 0);

}

QSize PasswordWidget::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Add enough space for the progress bar
    QSize size = QItemDelegate::sizeHint(option, index);
    size.setWidth(size.width() + 105);
    return size;
}

int PasswordWidget::getStrength(const QString &password) const
{
    // Password strength calculator borrowed from kwallet.cpp
    int pwstrength = (20 * password.length() + 80 * effectivePasswordLength(password)) / qMax(reasonablePasswordLength, 2);
    if (pwstrength < 0) {
        pwstrength = 0;
    } else if (pwstrength > 100) {
        pwstrength = 100;
    }
    return pwstrength;
}

// Borrowed from kwallet.cpp :)
int PasswordWidget::effectivePasswordLength(const QString &password) const
{
    enum Category {
        Digit,
        Upper,
        Vowel,
        Consonant,
        Special
    };

    Category previousCategory = Vowel;
    int count = 0;

    for (int i = 0; i < password.length(); ++i) {
        QChar currentChar = password.at(i);
        if (!password.left(i).contains(currentChar)) {
            Category currentCategory;
            switch (currentChar.category()) {
                case QChar::Letter_Uppercase:
                    currentCategory = Upper;
                    break;
                case QChar::Letter_Lowercase:
                    if (vwl.contains(currentChar)) {
                        currentCategory = Vowel;
                    } else {
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
            switch (currentCategory) {
                case Vowel:
                    if (previousCategory != Consonant) {
                        ++count;
                    }
                    break;
                case Consonant:
                    if (previousCategory != Vowel) {
                        ++count;
                    }
                    break;
                default:
                    if (previousCategory != currentCategory) {
                        ++count;
                    }
                    break;
            }
            previousCategory = currentCategory;
        }
    }
    return count;
}
