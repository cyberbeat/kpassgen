#ifndef STRENGTHBAR_H
#define STRENGTHBAR_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>

class PasswordWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PasswordWidget(const QString &password, QWidget *parent = 0);

public slots:
    void setPassword(const QString &pass);

private:
    int effectivePasswordLength(const QString &password);

    int reasonablePasswordLength;
    QLabel *m_text;
    QProgressBar *m_strengthbar;

};

#endif // STRENGTHBAR_H
