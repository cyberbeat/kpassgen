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
#include "mainwindow.h"
#include "settings.h"

#include <QApplication>
#include <QClipboard>
#include <QtGui/QWidget>
#include <QString>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QTabWidget>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBox>

#include <KLocale>
#include <KLineEdit>
#include <KPushButton>
#include <KShortcut>
#include <KIntSpinBox>
#include <KListWidget>
#include <KActionCollection>
#include <KAction>

MainWindow::MainWindow(QWidget *parent) :
	KXmlGuiWindow(parent)
{
	setupConfig();

	m_Length			= new KIntSpinBox(1, 999, 1, 12, this);
	m_Type				= new QComboBox;
	m_PasswordBox		= new PasswordList;
	m_GenerateButton	= new KPushButton(i18n("&Generate"));
	m_CopyButton		= new KPushButton(KIcon("edit-copy"), i18n("&Copy"));
	m_ExpandButton		= new KPushButton(i18n("&More >"));
	m_OptionTab			= new QToolBox;
	m_AlphanumericalPage = new AlphanumericalPage;
	m_HexPage			= new HexPage;
	m_OptionsPage		= new OptionsPage;

	setupActions();

	m_Type->addItem(i18n("Alphanumerical"));
	m_Type->addItem(i18n("Hex"));
	m_OptionTab->addItem(m_AlphanumericalPage, i18n("&Alphanumerical"));
	m_OptionTab->addItem(m_HexPage, i18n("Hex"));
	m_OptionTab->addItem(m_OptionsPage, i18n("General Options"));

	m_OptionTab->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	m_OptionTab->setMinimumSize(m_OptionTab->sizeHint());

	m_PasswordBox->addAction(actionCollection()->action("edit-copy"));
	m_PasswordBox->addAction(actionCollection()->action("monoToggle"));
	actionCollection()->action("edit-copy")->setEnabled(false);
	m_CopyButton->setEnabled(false);
	m_ExpandButton->setCheckable(true);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	QVBoxLayout* vLayout1   = new QVBoxLayout;
	QHBoxLayout* hLayout1   = new QHBoxLayout;
	QHBoxLayout* hLayout2   = new QHBoxLayout;

	mainLayout->addLayout(vLayout1, 1);
	vLayout1->addLayout(hLayout1);
	hLayout1->addWidget(new QLabel(i18n("Length of Passwords: ")));
	hLayout1->addWidget(m_Length);
	hLayout1->addWidget(m_Type);
	vLayout1->addWidget(m_PasswordBox);
	vLayout1->addLayout(hLayout2);
	hLayout2->addWidget(m_GenerateButton, 1);
	hLayout2->addWidget(m_CopyButton, 0);
	hLayout2->addWidget(m_ExpandButton, 0);

	mainLayout->addWidget(m_OptionTab, 0);

	QWidget* widget = new QWidget;
	widget->setLayout(mainLayout);
	setCentralWidget(widget);

	m_OptionTab->hide();

	connect(m_GenerateButton,		SIGNAL(clicked()),			this, SLOT(genPassword()));
	connect(m_CopyButton,			SIGNAL(clicked()),			this, SLOT(copy()));
	connect(m_ExpandButton,			SIGNAL(toggled(bool)),		this, SLOT(expandOptions(bool)));
	connect(m_Length,				SIGNAL(valueChanged(int)), 	this, SLOT(setNumberOfCharacters(int)));
	connect(m_Type,					SIGNAL(currentIndexChanged(int)),		this, SLOT(setType(int)));

	setupGUI(Save | StatusBar);

	updateSettings();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupActions()
{
	KAction* copyAction = new KAction(this);
	copyAction->setText(i18n("&Copy"));
	copyAction->setIcon(KIcon("edit-copy"));
	copyAction->setShortcut(KShortcut("Ctrl+C"));
	actionCollection()->addAction("edit-copy", copyAction);

	KAction* monoToggle = new KAction(this);
	monoToggle->setText(i18n("&Toggle mono spaced font"));
	monoToggle->setCheckable(true);
	actionCollection()->addAction("monoToggle", monoToggle);

	connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));
	connect(monoToggle, SIGNAL(toggled(bool)), this, SLOT(monoToggle(bool)));
}

void MainWindow::setupConfig()
{
	Settings::self()->readConfig();
}

void MainWindow::updateSettings()
{
	m_Length->setValue(Settings::numberOfCharacters());
	m_Type->setCurrentIndex(Settings::type());
	actionCollection()->action("monoToggle")->setChecked(Settings::monoFont());
	m_AlphanumericalPage->updateSettings();
	m_HexPage->updateSettings();
	m_OptionsPage->updateSettings();
}

void MainWindow::genPassword()
{
	QString list;

	clear();

	addPassword(GeneratePassword::generatePasswords());

	actionCollection()->action("edit-copy")->setEnabled(true);
	m_CopyButton->setEnabled(true);
}

void MainWindow::copy()
{
	QClipboard* clipboard = QApplication::clipboard();

	if ( m_PasswordBox->currentRow() < 0 )
		m_PasswordBox->setCurrentRow(0);
	QString text;
	text = m_PasswordBox->currentItem()->text();
	clipboard->setText(text);
}

void MainWindow::monoToggle(bool b)
{
	if( b )
		m_PasswordBox->setFont(QFont("Courier"));
	else
		m_PasswordBox->setFont(QFont("AnyStyle"));
	Settings::setMonoFont(b);
}

void MainWindow::expandOptions(bool b)
{
	if (b)
	{
		m_ExpandButton->setText(i18n("&Less <"));
	}
	else
	{
		m_ExpandButton->setText(i18n("&More >"));
	}
	m_OptionTab->setVisible(b);
}

void MainWindow::setNumberOfCharacters(int i)
{
    Settings::setNumberOfCharacters(i);
}

void MainWindow::setType(int i)
{
    Settings::setType(i);

}

void MainWindow::closeEvent(QCloseEvent* e)
{

	Settings::self()->writeConfig();
}
