#include "optionspage.h"
#include "ui_optionspage.h"
#include "settings.h"

#include <KLocale>

OptionsPage::OptionsPage(QWidget *parent) :
    QWidget(parent),
	ui(new Ui::OptionsPage)
{
	ui->setupUi(this);

	connect(ui->numberOfPasswords, SIGNAL(valueChanged(int)), this, SLOT(numberOfPasswordsChanged(int)));
	connect(ui->noSimilar, SIGNAL(toggled(bool)), this, SLOT(noSimular(bool)));
	connect(ui->unique, SIGNAL(toggled(bool)), this, SLOT(unique(bool)));
}

OptionsPage::~OptionsPage()
{
	delete ui;
}

void OptionsPage::updateSettings()
{
	ui->numberOfPasswords->setValue(Settings::numberOfPasswords());
	ui->noSimilar->setChecked(Settings::noSimilarCharacter());
	ui->unique->setChecked(Settings::uniqueCharacters());
}

void OptionsPage::numberOfPasswordsChanged(int i)
{
	Settings::setNumberOfPasswords(i);
}

void OptionsPage::noSimular(bool i)
{
	Settings::setNoSimilarCharacter(i);
}

void OptionsPage::unique(bool i)
{
	Settings::setUniqueCharacters(i);
}

void OptionsPage::changeEvent(QEvent *e)
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
