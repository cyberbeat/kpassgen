#ifndef COMMONDEF_H
#define COMMONDEF_H

#include <QFlags>
#include <QWidget>
//typedef KPassGen::AlphaChars QFlags<KPassGen::AlphaChar>;

class KPassGen
{
public:
	enum Type { Alphanumerical = 0, Hex = 1 };
	enum AlphaChar { Lower = 1, Upper = 2, Numbers = 4, Symbols = 8 };
	Q_DECLARE_FLAGS(AlphaChars, AlphaChar)
	//enum HexChars	{ HexLower = 0, Upper = 1 };
};
Q_DECLARE_OPERATORS_FOR_FLAGS(KPassGen::AlphaChars)
#endif // COMMONDEF_H
