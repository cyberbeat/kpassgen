#include "generatepassword.h"
#include "settings.h"

QStringList GeneratePassword::lastPasswords;
QString GeneratePassword::pickedCharacters;

QStringList	GeneratePassword::generatePasswords()
{
	lastPasswords.clear();

	while( lastPasswords.count() < Settings::numberOfPasswords() )
	{
		switch( Settings::type() ) {
			case 1:
				if( Settings::simple() )
					lastPasswords.append(generateAlphaSimplePassword());
				else
					lastPasswords.append(generateHexPassword());
				break;
			default:
				lastPasswords.append(generateAlphaPassword());
			}
	}

	return lastPasswords;
}

QStringList	GeneratePassword::getAlphaCharacterList()
{
	QStringList characterSets;
	for( int i = 0; i < Settings::checkedList().count(); ++i )
	{
		if( Settings::checkedList()[i] )
			characterSets.append(Settings::characterList()[i]);

	}
	return characterSets;
}

QList<int>	GeneratePassword::getAlphaMinimumList()
{
	QList<int> minimumList;
	for( int i = 0; i < Settings::checkedList().count(); ++i )
	{
		if( Settings::checkedList()[i] )
			minimumList.append(Settings::minimumList()[i]);

	}
	return minimumList;
}

QString	GeneratePassword::getAlphaCharacters()
{
	QString characters;

	for( int i = 0; i < getAlphaCharacterList().count(); ++i )
		characters.append(getAlphaCharacterList()[i]);

	return characters;
}

QString	GeneratePassword::getHexCharacters()
{
	if( Settings::hexLower() )
		return QString(i18n("0123456789abcdef"));
	else return QString(i18n("0123456789ABCDEF"));
}


QString GeneratePassword::generateAlphaPassword()
{
	pickedCharacters.clear();
	int totalMinimum = 0;
	for( int i = 0; i < getAlphaCharacterList().count(); ++i)
	{
		chooseCharacters(getAlphaCharacterList()[i], getAlphaMinimumList()[i]);
		totalMinimum += getAlphaMinimumList()[i];
	}

	chooseCharacters(getAlphaCharacters(), Settings::numberOfCharacters() - totalMinimum);
//	QTextStream(stdout) <<"MinimumTotal: " << totalMinimum  << "\tPicked: " << pickedCharacters
//			<< "\tNumber of picked: " << pickedCharacters.count() << endl;
	QString password;
	while( pickedCharacters.count() )
	{
		int index = qrand() % pickedCharacters.count();
		password.append(pickedCharacters[index]);
		pickedCharacters.remove(index, 1);
	}

	return password;
}

QString GeneratePassword::generateAlphaSimplePassword()
{
	pickedCharacters.clear();
	return QString("test");
}

QString GeneratePassword::generateHexPassword()
{
	pickedCharacters.clear();
	QString password;
	password.append(chooseCharacters(getHexCharacters(), Settings::numberOfCharacters()));
	return password;
}

QString GeneratePassword::chooseCharacters(QString characterSet, int count)
{
	if( count <= 0 )
		return QString();

	if( Settings::noSimilarCharacter() )
	{
		characterSet.remove(QRegExp("[" + ambiguous + "]"));
		characterSet.remove(QRegExp("[" + pickedCharacters + "]"));
	}

	QString characters;

	while( characters.count() < count )
	{
		if( characterSet.isEmpty() )
		{
			QTextStream(stdout) << "No more characters to pick from returning earily" << endl;
			return characters;
		}

		int picked = qrand() % characterSet.count();
		characters.append(characterSet[picked]);

		if( Settings::uniqueCharacters() )
			characterSet.remove(picked, 1);
	}
	pickedCharacters.append(characters);
	return characters;
}
