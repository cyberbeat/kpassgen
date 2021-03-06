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
#include "ui_kpassgen.h"
#include "generatepassword.h"
#include "passwordview.h"
#include "common.h"

#include <QApplication>
#include <QClipboard>
#include <QWidget>
#include <QString>
#include <QStringList>
#include "kpassgen.h"

#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>

MainWindow::MainWindow ( QWidget *parent ) :
        KXmlGuiWindow ( parent ),
        ui ( new Ui::KPassGen )
{
    QWidget *widget = new QWidget;
    ui->setupUi ( widget );

    setCentralWidget(widget);

    setupActions();
    setupContextMenu();

    setupGUI ( Create | Save );

    ui->optionspane->setVisible ( true );

	ui->passwordView->setModel(&model);

    ui->passwordView->setSelectionBehavior(QAbstractItemView::SelectRows);
    QHeaderView *header = ui->passwordView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    header->setSectionResizeMode(1, QHeaderView::Interactive);

    readSettings();

	connect ( ui->buttonOptions,      SIGNAL ( clicked() ),
              this,                    SLOT ( toggleOptions() ) );
    connect ( ui->buttonGenerate,      SIGNAL ( clicked() ),
              this,                    SLOT ( genPass() ) );
    connect ( ui->checkAlphaCustom,    SIGNAL ( toggled ( bool ) ),
              this,                    SLOT ( alphaUpdate() ) );
    connect ( ui->checkAlphaLowercase, SIGNAL ( toggled ( bool ) ),
              this,                    SLOT ( alphaUpdate() ) );
    connect ( ui->checkAlphaUppercase, SIGNAL ( toggled ( bool ) ),
              this,                    SLOT ( alphaUpdate() ) );
    connect ( ui->checkAlphaNumbers,   SIGNAL ( toggled ( bool ) ),
              this,                    SLOT ( alphaUpdate() ) );
    connect ( ui->checkAlphaSymbols,   SIGNAL ( toggled ( bool ) ),
              this,                    SLOT ( alphaUpdate() ) );
    connect ( ui->checkAlphaUnique,    SIGNAL ( toggled ( bool ) ),
              this,                    SLOT ( uniqueToggle ( bool ) ) );
    connect ( ui->lineAlphaCustom,     SIGNAL ( textChanged ( QString ) ),
              this,                    SLOT ( alphaUpdate() ) );
    connect ( ui->comboType,           SIGNAL ( currentIndexChanged ( int ) ),
              this,                    SLOT ( pageIndexChanged ( int ) ) );
    connect ( ui->buttonCopy,          SIGNAL ( clicked() ),
              this,                    SLOT ( copy() ) );
    connect ( ui->passwordView->selectionModel(),
              SIGNAL ( currentRowChanged( QModelIndex,QModelIndex ) ),
              this, SLOT ( selectionChanged( QModelIndex, QModelIndex ) ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupActions()
{
    QAction * copyAction = new QAction ( this );
    copyAction->setText ( i18n ( "&Copy" ) );
    copyAction->setIcon ( QIcon ( "edit-copy" ) );
    copyAction->setShortcut ( QKeySequence ( "Ctrl+C" ) );
    copyAction->setEnabled ( false );
    actionCollection()->addAction ( "edit-copy", copyAction );

    QAction * clearAction = new QAction ( this );
    clearAction->setText ( i18n ( "Clear &Passwords" ) );
    clearAction->setIcon ( QIcon::fromTheme(QStringLiteral("edit-clear")) );
    clearAction->setShortcut ( QKeySequence ( "Ctrl+D" ) );
    actionCollection()->addAction ( "edit-clear", clearAction );

    QAction * monoToggle = new QAction ( this );
    monoToggle->setText ( i18n ( "&Toggle mono spaced font" ) );
    monoToggle->setCheckable ( true );
    monoToggle->setChecked ( Settings::monoFont() );
    actionCollection()->addAction ( "monoToggle", monoToggle );

    connect ( copyAction, SIGNAL ( triggered() ), this, SLOT ( copy() ) );
    connect ( clearAction, SIGNAL ( triggered() ), this, SLOT ( clear() ) );
    connect ( monoToggle, SIGNAL ( toggled ( bool ) ), this, SLOT ( setMonoFont ( bool ) ) );
}

void MainWindow::setupContextMenu()
{
    ui->passwordView->addAction ( actionCollection()->action ( "edit-copy" ) );
    ui->passwordView->addAction ( actionCollection()->action ( "edit-clear" ) );
    ui->passwordView->setContextMenuPolicy ( Qt::ActionsContextMenu );
}

void MainWindow::closeEvent ( QCloseEvent* /*e*/ )
{
    writeSettings();
}

void MainWindow::writeSettings()
{
    Settings::setMonoFont ( actionCollection()->action ( "monoToggle" )->isChecked() );
    Settings::setAlphaCustom ( ui->checkAlphaCustom->isChecked() );
    Settings::setAlphaLowercase ( ui->checkAlphaLowercase->isChecked() );
    Settings::setAlphaNumbers ( ui->checkAlphaNumbers->isChecked() );
    Settings::setAlphaSymbols ( ui->checkAlphaSymbols->isChecked() );
    Settings::setAlphaUnambiguous ( ui->checkAlphaUnambiguous->isChecked() );
    Settings::setAlphaUnique ( ui->checkAlphaUnique->isChecked() );
    Settings::setAlphaUppercase ( ui->checkAlphaUppercase->isChecked() );
    Settings::setOptionsVisable ( ui->buttonOptions->isChecked() );
    Settings::setType ( ui->comboType->currentIndex() );
    Settings::setAlphaCustomText ( ui->lineAlphaCustom->text() );
    Settings::setHexLower ( ui->radioHexLower->isChecked() );
    Settings::setAmount ( ui->spinAmount->value() );
    Settings::setLength ( ui->spinLength->value() );
    Settings::setPernUpper ( ui->checkPernUpper->isChecked() );
    Settings::setPernNumber ( ui->checkPernNumber->isChecked() );
    Settings::setPernUnambigous ( ui->checkPernUnam->isChecked() );
    Settings::self()->writeConfig();
}

void MainWindow::readSettings()
{
    Settings::self()->readConfig();
    ui->checkAlphaCustom->setChecked ( Settings::alphaCustom() );
    ui->checkAlphaLowercase->setChecked ( Settings::alphaLowercase() );
    ui->checkAlphaNumbers->setChecked ( Settings::alphaNumbers() );
    ui->checkAlphaSymbols->setChecked ( Settings::alphaSymbols() );
    ui->checkAlphaUnambiguous->setChecked ( Settings::alphaUnambiguous() );
    ui->checkAlphaUnique->setChecked ( Settings::alphaUnique() );
    ui->checkAlphaUppercase->setChecked ( Settings::alphaUppercase() );
    ui->buttonOptions->setChecked ( Settings::optionsVisable() );
    ui->comboType->setCurrentIndex ( Settings::type() );
    ui->lineAlphaCustom->setText ( Settings::alphaCustomText() );
    ui->radioHexLower->setChecked ( Settings::hexLower() );
    ui->spinAmount->setValue ( Settings::amount() );
    ui->spinLength->setValue ( Settings::length() );
    ui->passwordView->setMonoFont ( Settings::monoFont() );
    ui->checkPernUpper->setChecked ( Settings::pernUpper() );
    ui->checkPernNumber->setChecked ( Settings::pernNumber() );
    ui->checkPernUnam->setChecked ( Settings::pernUnambigous() );
    pageIndexChanged ( ui->comboType->currentIndex() );
}

void MainWindow::toggleOptions()
{
	ui->optionspane->setVisible(!ui->optionspane->isVisible());
}

void MainWindow::genPass()
{

    QFlags<GeneratePassword::Option> flags;
    QString characterset;
    QStringList passlist;

    switch ( ui->comboType->currentIndex() )
    {
    case 0:
        if ( ui->checkAlphaUnambiguous->isChecked() )
            flags |= GeneratePassword::Unambiguous;

        if ( ui->checkAlphaUnique->isChecked() )
            flags |= GeneratePassword::Unique;

        characterset = getCharacterSet();

        passlist = GeneratePassword::genRandom (
                       ui->spinLength->value(), characterset,
                       ui->spinAmount->value(), flags );
        break;
    case 1:
        if ( ui->radioHexLower->isChecked() )
            characterset = hex_set.toLower();
        else
            characterset = hex_set;

        passlist = GeneratePassword::genRandom (
                       ui->spinLength->value(), characterset,
                       ui->spinAmount->value(), flags );
        break;
    case 2:
        if ( ui->checkPernUnam->isChecked() )
            flags |= GeneratePassword::Unambiguous;

        if ( ui->checkPernNumber->isChecked() )
            flags |= GeneratePassword::Number;

        if ( ui->checkPernUpper->isChecked() )
            flags |= GeneratePassword::Upper;

        passlist = GeneratePassword::genPernouncable ( ui->spinLength->value(),
                   ui->spinAmount->value(),
                   flags );
        break;
    }

    model.clear();

    foreach( QString pass, passlist) {
        model.addPassword(pass);
    }
}

void MainWindow::pageIndexChanged ( int index )
{
    switch ( index )
    {
    case 0:
        alphaUpdate();
        break;
    case 1:
        ui->spinLength->setMaximum ( 1024 );
        ui->spinLength->setMinimum ( 1 );
        break;
    case 2:
        ui->spinLength->setMaximum ( 1024 );
        ui->spinLength->setMinimum ( 3 );
    }
}

void MainWindow::alphaUpdate()
{
    bool lower   = ui->checkAlphaLowercase->isChecked();
    bool upper   = ui->checkAlphaUppercase->isChecked();
    bool symbol  = ui->checkAlphaSymbols->isChecked();
    bool number  = ui->checkAlphaNumbers->isChecked();
    bool custom  = ui->checkAlphaCustom->isChecked();
    int count = 0;

    if ( lower ) count++;
    if ( upper ) count++;
    if ( symbol ) count++;
    if ( number ) count++;
    if ( custom ) count++;

    if ( count == 0 )
    {
        ui->checkAlphaLowercase->setChecked ( true );
    }
    else if ( count == 1 )
    {
        if ( lower )
        {
            ui->checkAlphaLowercase->setEnabled ( false );
        }
        else if ( upper )
        {
            ui->checkAlphaUppercase->setEnabled ( false );
        }
        else if ( symbol )
        {
            ui->checkAlphaSymbols->setEnabled ( false );
        }
        else if ( number )
        {
            ui->checkAlphaNumbers->setEnabled ( false );
        }
        else if ( custom )
        {
            ui->checkAlphaCustom->setEnabled ( false );
        }
    }
    else
    {
        ui->checkAlphaLowercase->setEnabled ( true );
        ui->checkAlphaUppercase->setEnabled ( true );
        ui->checkAlphaSymbols->setEnabled ( true );
        ui->checkAlphaNumbers->setEnabled ( true );
        ui->checkAlphaCustom->setEnabled ( true );
    }
    uniqueToggle ( ui->checkAlphaUnique->isChecked() );
    ui->spinLength->setMinimum ( 1 );
}

void MainWindow::uniqueToggle ( bool unique )
{
    if ( unique )
    {
        int max = 1024;
        int charlength = getCharacterSet().length();
        if ( max > charlength )
            max = charlength;
        ui->spinLength->setMaximum ( max );
    }
    else
    {
        ui->spinLength->setMaximum ( 1024 );
    }
}

void MainWindow::copy()
{
    ui->passwordView->copyCurrentItem();
}

void MainWindow::clear()
{
    (( PasswordModel* ) ui->passwordView->model() )->clear();
}

void MainWindow::setMonoFont ( bool b )
{
    ui->passwordView->setMonoFont ( b );
}

void MainWindow::selectionChanged ( QModelIndex current, QModelIndex previous )
{
    setCopyEnabled( current.isValid() );
}

void MainWindow::setCopyEnabled ( bool enabled )
{
    ui->buttonCopy->setEnabled( enabled );
    actionCollection()->action( "edit-copy" )->setEnabled( enabled );
}

void MainWindow::setCopyDisabled ( bool enabled )
{
    setCopyEnabled( !enabled );
}

QString MainWindow::getCharacterSet()
{
    QString characterset;

    if ( ui->checkAlphaLowercase->isChecked() )
        characterset += lowercase_set;

    if ( ui->checkAlphaUppercase->isChecked() )
        characterset += uppercase_set;

    if ( ui->checkAlphaSymbols->isChecked() )
        characterset += symbol_set;

    if ( ui->checkAlphaNumbers->isChecked() )
        characterset += number_set;

    if ( ui->checkAlphaUnambiguous->isChecked() )
        for ( int i = 0; i < ambiguous_set.length(); i++ )
            characterset.remove ( ambiguous_set[i] );

    if ( ui->checkAlphaCustom->isChecked() )
        characterset += ui->lineAlphaCustom->text();

    return characterset;
}

void MainWindow::changeEvent ( QEvent* e )
{
    QWidget::changeEvent ( e );
    switch ( e->type() )
    {
    case QEvent::LanguageChange:
        ui->retranslateUi ( this );
        break;
    default:
        break;
    }
}
