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

#include "passwordview.h"
#include "passwordmodel.h"

#include <qt5/QtWidgets/QWidget>
#include <qt5/QtCore/QStringList>
#include <KF5/KXmlGui/KXmlGuiWindow>

namespace Ui {
    class KPassGen;
}

class MainWindow : public KXmlGuiWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setCopyEnabled(bool enabled = true);
    void setCopyDisabled(bool enabled = true);
	void toggleOptions();
    void genPass();
    void pageIndexChanged(int index);
    void alphaUpdate();
    void uniqueToggle(bool unique);
    void copy();
    void clear();
    void setMonoFont(bool b = false);
    void selectionChanged(QModelIndex current, QModelIndex previous);

private:
    void setupActions();
    void setupContextMenu();
    void writeSettings();
    void readSettings();

    QString getCharacterSet();
    Ui::KPassGen *ui;
    PasswordModel model;

protected:
    void closeEvent(QCloseEvent* e);
    void changeEvent(QEvent *e);
};

#endif // MAINWINDOW_H
