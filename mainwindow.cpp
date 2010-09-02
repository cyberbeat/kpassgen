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
#include "ui_mainwindow.h"
#include "settings.h"
#include "kpassgen.h"

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
    setCentralWidget(new KPassGen);
    setupConfig();

    setupActions();

    updateSettings();
    setupGUI(Create | Save | StatusBar);
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
	copyAction->setEnabled(false);
	actionCollection()->addAction("edit-copy", copyAction);

	KAction* monoToggle = new KAction(this);
	monoToggle->setText(i18n("&Toggle mono spaced font"));
	monoToggle->setCheckable(true);
	actionCollection()->addAction("monoToggle", monoToggle);

//	connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));
//	connect(monoToggle, SIGNAL(toggled(bool)), this, SLOT(monoToggle(bool)));
}

void MainWindow::setupConfig()
{
	Settings::self()->readConfig();
}

void MainWindow::updateSettings()
{
/*
	m_sLength->setValue(Settings::numberOfCharacters());
	m_Type->setCurrentIndex(Settings::type());
	actionCollection()->action("monoToggle")->setChecked(Settings::monoFont());
	m_AlphanumericalPage->updateSettings();
	m_HexPage->updateSettings();
	m_OptionsPage->updateSettings();
	*/
}

void MainWindow::closeEvent(QCloseEvent* e)
{

	Settings::self()->writeConfig();
}
