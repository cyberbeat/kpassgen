#include "passwordwidget.h"

#include <QHBoxLayout>

PasswordWidget::PasswordWidget(const QString &password, QWidget *parent) :
    QWidget(parent), reasonablePasswordLength(12)
{
    m_text = new QLabel(password);
    m_strengthbar = new QProgressBar;

    m_strengthbar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);

    layout->addStretch(1);
    layout->addWidget(m_strengthbar);

    setPassword(password);
}

void PasswordWidget::setPassword(const QString &password)
{
    // Password strength calculator borrowed from kwallet.cpp
    int pwstrength = (20 * password.length() + 80 * effectivePasswordLength(password)) / qMax(reasonablePasswordLength, 2);
    if (pwstrength < 0) {
        pwstrength = 0;
    } else if (pwstrength > 100) {
        pwstrength = 100;
    }
    m_strengthbar->setValue(pwstrength);
}

// Borrowed from kwallet.cpp :)
int PasswordWidget::effectivePasswordLength(const QString &password)
{
    enum Category {
        Digit,
        Upper,
        Vowel,
        Consonant,
        Special
    };

    Category previousCategory = Vowel;
    QString vowels("aeiou");
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
                    if (vowels.contains(currentChar)) {
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
