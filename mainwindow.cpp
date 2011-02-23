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
#include "kpassgen.h"
#include "ui_kpassgen.h"
#include "generatepassword.h"
#include "passwordview.h"
#include "common.h"

#include <QApplication>
#include <QClipboard>
#include <QtGui/QWidget>
#include <QString>
#include <QStringList>
#include <QDebug>

#include <KLocale>
#include <KActionCollection>
#include <KAction>

MainWindow::MainWindow ( QWidget *parent ) :
        KXmlGuiWindow ( parent )
{
    setupConfig();
    passwidget = new KPassGen ( this );
    setCentralWidget ( passwidget );

    setupActions();
    setupContextMenu();

    setupGUI ( Create | Save );

    connect ( passwidget, SIGNAL ( passwordsChanged() ), this, SLOT ( enableCopy() ) );
    connect ( passwidget, SIGNAL ( passwordsCleared() ), this, SLOT ( disableCopy() ) );
}

MainWindow::~MainWindow()
{
}

void MainWindow::enableCopy ( bool b )
{
    actionCollection()->action ( "edit-copy" )->setEnabled ( b );
    actionCollection()->action ( "edit-clear" )->setEnabled ( b );
    passwidget->setCopyEnabled ( b );
}

void MainWindow::disableCopy ( bool b )
{
    enableCopy ( !b );
}

void MainWindow::setupActions()
{
    KAction* copyAction = new KAction ( this );
    copyAction->setText ( i18n ( "&Copy" ) );
    copyAction->setIcon ( KIcon ( "edit-copy" ) );
    copyAction->setShortcut ( KShortcut ( "Ctrl+C" ) );
    copyAction->setEnabled ( false );
    actionCollection()->addAction ( "edit-copy", copyAction );

    KAction* clearAction = new KAction ( this );
    clearAction->setText ( i18n ( "Clear &Passwords" ) );
    clearAction->setIcon ( KIcon ( "edit-clear" ) );
    clearAction->setShortcut ( KShortcut ( "Ctrl+D" ) );
    clearAction->setEnabled ( false );
    actionCollection()->addAction ( "edit-clear", clearAction );

    KAction* monoToggle = new KAction ( this );
    monoToggle->setText ( i18n ( "&Toggle mono spaced font" ) );
    monoToggle->setCheckable ( true );
    monoToggle->setChecked ( Settings::monoFont() );
    actionCollection()->addAction ( "monoToggle", monoToggle );

    connect ( copyAction, SIGNAL ( triggered() ), passwidget, SLOT ( copy() ) );
    connect ( clearAction, SIGNAL ( triggered() ), passwidget, SLOT ( clear() ) );
    connect ( monoToggle, SIGNAL ( toggled ( bool ) ), passwidget, SLOT ( setMonoFont ( bool ) ) );
}

void MainWindow::setupContextMenu()
{
    passwidget->addAction ( actionCollection()->action ( "edit-copy" ) );
    passwidget->addAction ( actionCollection()->action ( "edit-clear" ) );
    passwidget->setContextMenuPolicy ( Qt::ActionsContextMenu );
}

void MainWindow::setupConfig()
{
    Settings::self()->readConfig();
}

void MainWindow::closeEvent ( QCloseEvent* /*e*/ )
{
    Settings::setMonoFont ( actionCollection()->action ( "monoToggle" )->isChecked() );
    passwidget->writeSettings();
    Settings::self()->writeConfig();
}

KPassGen::KPassGen ( QWidget *parent ) :
        QWidget ( parent ),
        ui ( new Ui::KPassGen )
{
    ui->setupUi ( this );
    ui->optionspane->setVisible ( false );
    ui->passwordView->setModel(&model);
    
    ui->passwordView->setSelectionBehavior(QAbstractItemView::SelectRows);
    QHeaderView *header = ui->passwordView->horizontalHeader();
    header->setResizeMode(QHeaderView::Stretch);
    header->setResizeMode(1, QHeaderView::Interactive);

    readSettings();

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

KPassGen::~KPassGen()
{
    delete ui;
}

void KPassGen::writeSettings()
{
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
}

void KPassGen::readSettings()
{
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

void KPassGen::genPass()
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
    emit passwordsChanged();
}

void KPassGen::pageIndexChanged ( int index )
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

void KPassGen::alphaUpdate()
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

void KPassGen::uniqueToggle ( bool unique )
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

void KPassGen::copy()
{
    ui->passwordView->copyCurrentItem();
}

void KPassGen::clear()
{
    //TODO
    //ui->listPasswords->clear();
    emit passwordsCleared();
}

void KPassGen::setMonoFont ( bool b )
{
    ui->passwordView->setMonoFont ( b );
}

void KPassGen::selectionChanged(QModelIndex current, QModelIndex previous)
{
    qDebug() << "Index: " << current.row() << " " << current.column();
    bool enable = current.isValid();
    ui->buttonCopy->setEnabled(enable);
}

void KPassGen::setCopyEnabled ( bool b )
{
    qDebug() << "setCopyEnabled not used";
    //ui->buttonCopy->setEnabled ( b );
}

QString KPassGen::getCharacterSet()
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

void KPassGen::changeEvent ( QEvent* e )
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
