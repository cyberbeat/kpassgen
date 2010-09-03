#include "kpassgen.h"
#include "ui_kpassgen.h"
#include "generatepassword.h"

#include <QStringList>
#include <KDebug>

const QString lowercaseset("abcdefghijklmnopqrstuvwxyz");
const QString uppercaseset("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
const QString symbolset("¬`!\"£$%^&*()_+-={}[];'#:@~<>?,./|\\ ");
const QString numberset("0123456789");
const QString hexset("0123456789ABCDEF");

KPassGen::KPassGen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KPassGen)
{
    ui->setupUi(this);
    ui->optionspane->setVisible(false);

    connect(ui->buttonGenerate, SIGNAL(clicked()), this, SLOT(genPass()));
}

KPassGen::~KPassGen()
{
    delete ui;
}

void KPassGen::genPass() {

    QFlags<GeneratePassword::Option> flags;
    QString characterset;

    kDebug() << "KPassGen::genPass - currentIndex: " << ui->comboType->currentIndex();

    switch(ui->comboType->currentIndex()) {
    case 0:
        if (ui->checkAlphaUnambiguous->isChecked())
            flags |= GeneratePassword::Unambiguous;

        if (ui->checkAlphaUnique->isChecked())
            flags |= GeneratePassword::Unique;


        if (ui->checkAlphaLowercase->isChecked())
            characterset += lowercaseset;

        if (ui->checkAlphaUppercase->isChecked())
            characterset += uppercaseset;

        if (ui->checkAlphaSymbols->isChecked())
            characterset += symbolset;

        if (ui->checkAlphaNumbers->isChecked())
            characterset += numberset;

        if (ui->checkAlphaCustom->isChecked())
            characterset += ui->lineAlphaCustom->text();

        break;
    case 1:
        if (ui->radioHexLower->isChecked())
            characterset = hexset.toLower();
        else
            characterset = hexset;
    }

    kDebug() << "KPassGen::genPass - characterset: " << characterset;

    QStringList passlist = GeneratePassword::genAlphanumerical(
                ui->spinLength->value(), characterset,
                ui->spinAmount->value(), flags);

    ui->listPasswords->replace(passlist);
}

void KPassGen::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
