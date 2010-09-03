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

    readSettings();

    connect(ui->buttonGenerate, SIGNAL(clicked()),
            this, SLOT(genPass()));
    connect(ui->checkAlphaCustom, SIGNAL(toggled(bool)),
            this, SLOT(alphaSetToggle()));
    connect(ui->checkAlphaLowercase, SIGNAL(toggled(bool)),
            this, SLOT(alphaSetToggle()));
    connect(ui->checkAlphaUppercase, SIGNAL(toggled(bool)),
            this, SLOT(alphaSetToggle()));
    connect(ui->checkAlphaNumbers, SIGNAL(toggled(bool)),
            this, SLOT(alphaSetToggle()));
    connect(ui->checkAlphaSymbols, SIGNAL(toggled(bool)),
            this, SLOT(alphaSetToggle()));
    connect(ui->checkAlphaUnique, SIGNAL(toggled(bool)),
            this, SLOT(uniqueToggle(bool)));
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
    alphaSetToggle();
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

        characterset = getCharacterSet();

        break;
    case 1:
        if (ui->radioHexLower->isChecked())
            characterset = hexset.toLower();
        else
            characterset = hexset;
    }

    kDebug() << "characterset: " << characterset;

    QStringList passlist = GeneratePassword::genAlphanumerical(
                ui->spinLength->value(), characterset,
                ui->spinAmount->value(), flags);

    ui->listPasswords->replace(passlist);
}

void KPassGen::alphaSetToggle()
{
    bool lower   = ui->checkAlphaLowercase->isChecked();
    bool upper   = ui->checkAlphaUppercase->isChecked();
    bool symbol  = ui->checkAlphaSymbols->isChecked();
    bool number  = ui->checkAlphaNumbers->isChecked();
    bool custom  = ui->checkAlphaCustom->isChecked();
    int count = 0;

    if (lower) count++;
    if (upper) count++;
    if (symbol) count++;
    if (number) count++;
    if (custom) count++;

    kDebug() << "count: " << count;

    if (count == 0) {
        ui->checkAlphaLowercase->setChecked(true);
    } else if (count == 1) {
        if (lower) {
            ui->checkAlphaLowercase->setEnabled(false);
        } else if (upper) {
            ui->checkAlphaUppercase->setEnabled(false);
        } else if (symbol) {
            ui->checkAlphaSymbols->setEnabled(false);
        } else if (number) {
            ui->checkAlphaNumbers->setEnabled(false);
        } else if (custom) {
            ui->checkAlphaCustom->setEnabled(false);
        }
    } else {
        ui->checkAlphaLowercase->setEnabled(true);
        ui->checkAlphaUppercase->setEnabled(true);
        ui->checkAlphaSymbols->setEnabled(true);
        ui->checkAlphaNumbers->setEnabled(true);
        ui->checkAlphaCustom->setEnabled(true);
    }
    uniqueToggle(ui->checkAlphaUnique->isChecked());
}

void KPassGen::uniqueToggle(bool unique)
{
    if (unique) {
        int max = 1024;
        int charlength = getCharacterSet().length();
        if (max > charlength)
            max = charlength;
        ui->spinLength->setMaximum(max);
    } else {
        ui->spinLength->setMaximum(1024);
    }
}

QString KPassGen::getCharacterSet()
{
    QString characterset;

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

    return characterset;
}

void KPassGen::changeEvent(QEvent* e)
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
