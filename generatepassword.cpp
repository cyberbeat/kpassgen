#include "generatepassword.h"
#include "settings.h"
#include "random.h"

QStringList GeneratePassword::genAlphanumerical(int length, QString &characterset,
                                       int amount, QFlags<Option> &flags)
{
    QStringList passwordList;

    while (passwordList.length() < amount) {
        QString password;

        while (password.length() < length) {
            password.append(characterset[random.nextInt(characterset.length())]);
            if (flags.testFlag(Unique))
                characterset.remove(random.nextInt(characterset.length(), 1));
        }
        passwordList.append(password);
    }

    return passwordList;
}

