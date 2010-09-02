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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "alphanumericalpage.h"
#include "hexpage.h"
#include "generatepassword.h"
#include "commondef.h"
#include "optionspage.h"
#include "passwordlist.h"

#include <QStringList>

#include <KXmlGuiWindow>

namespace Ui {
    class MainWindow;
}

class Settings;

class QCheckBox;
class QToolBox;
class QComboBox;

class KPushButton;
class KLineEdit;
class KIntSpinBox;
class KListWidget;

class MainWindow : public KXmlGuiWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void addPassword(QStringList pass)	{ m_PasswordBox->addItems(pass); }
	void clear()						{ m_PasswordBox->clear(); }

private slots:
	void genPassword();
	void copy();
	void monoToggle(bool b);
	void expandOptions(bool b);
	void setNumberOfCharacters(int i);
	void setType(int i);

private:
	void setupActions();
	void setupConfig();
	void updateSettings();

	GeneratePassword* m_GeneratePassword;
	Settings*		m_settings;
	KIntSpinBox*	m_Length;
	QComboBox*		m_Type;
	PasswordList*	m_PasswordBox;
	KPushButton*	m_GenerateButton;
	KPushButton*	m_CopyButton;
	KPushButton*	m_ExpandButton;
	QToolBox*		m_OptionTab;

    AlphanumericalPage* m_AlphanumericalPage;
	HexPage*			m_HexPage;
    OptionsPage*		m_OptionsPage;

    Ui::MainWindow*    m_ui;

protected:
	void closeEvent(QCloseEvent* e);
};

#endif // MAINWINDOW_H
