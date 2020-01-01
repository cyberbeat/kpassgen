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
#include "random.h"

#include <QApplication>
#include <KCoreAddons/KAboutData>
#include <QUrl>
#include <QTextStream>
#include <KLocalizedString>
#include <QCommandLineParser>
#include <KI18n/ki18n_export.h>

#include "kpassgen.h"

int main ( int argc, char *argv[] )
{
    KAboutData aboutData (
        "kpassgen",					//appName
        ki18n ( "KPassGen" ).toString(),			//programName
        "1.5",                      //version
        ki18n ( "Generates a set of random passwords of any "
                "length that can include the letter a-z, A-Z"
                " any number and symbols and any other character "
                "that QString can handle or hex values." ).toString(), //shortDescription
        KAboutLicense::GPL,
        ki18n ( "Copyright (c) 2009 Michael Daffin" ).toString() );
    QApplication app(argc, argv); // PORTING SCRIPT: move this to before the KAboutData initialization
    QCommandLineParser parser;
    KAboutData::setApplicationData(aboutData);
    parser.addVersionOption();
    parser.addHelpOption();
    //PORTING SCRIPT: adapt aboutdata variable if necessary
    aboutData.setupCommandLine(&parser);
    parser.process(app); // PORTING SCRIPT: move this to after any parser.addOption
    aboutData.processCommandLine(&parser);

    Random::init();


    MainWindow* window = new MainWindow();
    window->show();

    return app.exec();
}
