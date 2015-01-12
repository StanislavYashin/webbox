#pragma once

#include <qstring.h>

enum eGeneralFieldType
{
	GFT_INTEGER,
	GFT_STRING,
	GFT_GUID,
	GFT_OBJECT,
	GFT_DOUBLE,
	GFT_BYTE
};

struct GeneralField
{
public:

	QString				name;
	int					index;
	eGeneralFieldType	type;

	GeneralField(QString _name, int _index, eGeneralFieldType _type)
	{
		name = _name;
		index = _index;
		type = _type;
	}
};