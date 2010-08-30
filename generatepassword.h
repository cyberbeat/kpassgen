#ifndef GENERATEPASSWORD_H
#define GENERATEPASSWORD_H

#include "commondef.h"
#include "settings.h"

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFlags>
#include <KLocale>


class GeneratePassword : public QObject
{
	Q_OBJECT
public:
	static QStringList	getLastPasswords() { return lastPasswords; }
	static QStringList	generatePasswords();
	static QStringList	getAlphaCharacterList();
	static QList<int>	getAlphaMinimumList();
	static QString		getAlphaCharacters();
	static QString		getHexCharacters();

private:
	static QString generateAlphaPassword();
	static QString generateAlphaSimplePassword();
	static QString generateHexPassword();
	static QString chooseCharacters(const QString characterSet, int count);

	static QString getLower()	{ return QString(Settings::characterList()[KPassGen::Lower-1]); }
	static QString getUpper()	{ return QString(Settings::characterList()[KPassGen::Upper-1]); }
	static QString getNumber()	{ return QString(Settings::characterList()[KPassGen::Numbers-1]); }
	static QString getSymbol()	{ return QString(Settings::characterList()[KPassGen::Symbols-1]); }
	static QString getCharacterSet(int index)	{ return (index < Settings::characterList().count() ?
														  QString(Settings::characterList()[index]) :
														  QString()); }

	static QStringList lastPasswords;
	static QString pickedCharacters;

};


static const QString ambiguous = "B8G6I1l0OQDS5Z2";
#endif // GENERATEPASSWORD_H
