#pragma once
 
#include "GeneralField.hpp"
#include <qstring.h>
#include <qmap.h> 

class GeneralSchema
{
public:

	GeneralSchema()
		:fieldCount(0)
	{}

	virtual ~GeneralSchema()
	{}

	int getIndexByName(const QString &name)
	{
		if (_dictField.contains(name))
			return _dictField[name]->index;
		return -1;
	}

	GeneralField* getFieldByName(QString name)
	{
		return _dictField[name];
	}

	GeneralField* getFieldByIndex(int index)
	{
		QString fieldName = _dictName[index];
		return getFieldByName(fieldName); 
	}

	void setSchema(QString name, int index, eGeneralFieldType type)
	{
		fieldCount += 1;

		GeneralField *ptr_field = new GeneralField(name, index, type);
		_dictField[name]= ptr_field;
		_dictName[index]=QString(name);
	}

	void addSchema(QString name, int index, eGeneralFieldType type)
	{
		setSchema(name, index, type);
		/*GeneralField *ptr_field = new GeneralField(name, index, type);
		_dictField.insert(name, ptr_field);
		_dictName.insert(index, name);
		GeneralField *ptr_field = new GeneralField(name, index, type);
		_dictField[name] = ptr_field;
		_dictName[index] = name;*/
	}

	int count() const { return _dictField.count(); }

protected:

	int fieldCount;
	QMap<QString, GeneralField*>	_dictField;
	QMap<int, QString>				_dictName;
};  