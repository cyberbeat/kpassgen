#ifndef GENERATEPASSWORD_H
#define GENERATEPASSWORD_H

#include "random.h"

#include <QObject>
#include <QString>
#include <QFlags>


class GeneratePassword : public QObject
{
    Q_OBJECT
public:
    enum Option { None        = 0x0,
                  Unique      = 0x1,
                  Unambiguous = 0x2 };
    Q_DECLARE_FLAGS(Options, Option)

    static QStringList genAlphanumerical(int length, QString &characterset,
                            int amount, QFlags<Option> &flag);
//    static QString genPernouncable(int length, QString &characterset);
//    static QString genHex(int length, QString &characterset);

private:
//    static const QString ambiguous;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(GeneratePassword::Options)
//QString GeneratePassword::ambiguous = "B8G6I1l0OQDS5Z2";

#endif // GENERATEPASSWORD_H
