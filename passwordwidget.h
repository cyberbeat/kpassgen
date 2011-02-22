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

    int getStrength(const QString &pass) const;
    
public slots:

private:
    int effectivePasswordLength(const QString &password) const;
    
    int reasonablePasswordLength;

};

#endif // STRENGTHBAR_H
