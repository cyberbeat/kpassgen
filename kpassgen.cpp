/*
	Copyright 2009 Michael Daffin <james1479@googlemail.com>

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "kpassgen.h"
#include "generatepassword.h"
#include "settings.h"

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

bool KPassGen::writeSettings()
{
    Settings::setAlphaCustom(ui->checkAlphaCustom->isChecked());
    Settings::setAlphaLowercase(ui->checkAlphaLowercase->isChecked());
    Settings::setAlphaNumbers(ui->checkAlphaNumbers->isChecked());
    Settings::setAlphaSymbols(ui->checkAlphaSymbols->isChecked());
    Settings::setAlphaUnambiguous(ui->checkAlphaUnambiguous->isChecked());
    Settings::setAlphaUnique(ui->checkAlphaUnique->isChecked());
    Settings::setAlphaUppercase(ui->checkAlphaUppercase->isChecked());
    Settings::setOptionsVisable(ui->buttonOptions->isChecked());
    Settings::setType(ui->comboType->currentIndex());
    Settings::setAlphaCustomText(ui->lineAlphaCustom->text());
    Settings::setHexLower(ui->radioHexLower->isChecked());
    Settings::setAmount(ui->spinAmount->value());
    Settings::setLength(ui->spinLength->value());
}

bool KPassGen::readSettings()
{
    ui->checkAlphaCustom->setChecked(Settings::alphaCustom());
    ui->checkAlphaLowercase->setChecked(Settings::alphaLowercase());
    ui->checkAlphaNumbers->setChecked(Settings::alphaNumbers());
    ui->checkAlphaSymbols->setChecked(Settings::alphaSymbols());
    ui->checkAlphaUnambiguous->setChecked(Settings::alphaUnambiguous());
    ui->checkAlphaUnique->setChecked(Settings::alphaUnique());
    ui->checkAlphaUppercase->setChecked(Settings::alphaUppercase());
    ui->buttonOptions->setChecked(Settings::optionsVisable());
    ui->comboType->setCurrentIndex(Settings::type());
    ui->lineAlphaCustom->setText(Settings::alphaCustomText());
    ui->radioHexLower->setChecked(Settings::hexLower());
    ui->spinAmount->setValue(Settings::amount());
    ui->spinLength->setValue(Settings::length());
}

void KPassGen::genPass() {

    QFlags<GeneratePassword::Option> flags;
    QString characterset;

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
