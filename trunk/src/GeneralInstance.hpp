#pragma once

#include "GeneralSchema.hpp"
#include <QVariant.h>
#include <quuid.h>
#include <qlist.h>
#include <qdebug.h>
 
class GeneralInstance
{
public:
	
	GeneralInstance()
	{
		_schema = new GeneralSchema();
	}

	int getIndexByName(QString name)
	{
		if (_schema == NULL)
			return -1;

		return _schema->getIndexByName(name);
	}

	double getDouble(int index)
	{
		if (index >= 0 && index < _values.count())
			return _values[index]->toDouble();
		return -1;
	}

	double getDouble(QString name)
	{ 
		int index = _schema->getIndexByName(name); 
		return getDouble(index);
	}

	QString getString(int index)
	{
		return _values[index]->toString();
	}

	QString getString(QString name)
	{
		int index = _schema->getIndexByName(name);
		return getString(index);
	}

	int getInteger(int index)
	{
		return _values[index]->toInt();
	}

	int getInteger(QString name)
	{
		int index = _schema->getIndexByName(name);
		return getInteger(index);
	}
	
	QUuid getGuid(int index)
	{
		return _values[index]->toUuid();
	}

	QUuid getGuid(QString name)
	{
		int index = _schema->getIndexByName(name);
		return getGuid(index);
	}

	QByteArray getByte(int index)
	{
		return _values[index]->toByteArray();
	}

	QByteArray getByte(QString name)
	{
		int index = _schema->getIndexByName(name);
		return getByte(index);
	}

	QVariant *getValue(int index)
	{
		return _values[index];
	}

	QVariant *getValue(QString fieldName)
	{
		int index = getIndexByName(fieldName);
		return getValue(index);
	}

	void setByte(QString name, int index, QByteArray value)
	{
		_schema->addSchema(name, index, eGeneralFieldType::GFT_BYTE);
		_values[index] = new QVariant(value);
	}

	void setGuid(QString name, int index, QUuid value)
	{
		_schema->addSchema(name, index, eGeneralFieldType::GFT_GUID);
		_values[index] = new QVariant(value);
	}

	void setDouble(QString name, int index, double value)
	{
		_schema->addSchema(name, index, eGeneralFieldType::GFT_DOUBLE);
		_values[index] = new QVariant(value);
	}

	void setString(QString name, int index, QString value)
	{
		_schema->addSchema(name, index, eGeneralFieldType::GFT_STRING);
		_values[index] = new QVariant(value);
	}

	void setInteger(QString name, int index, int value)
	{
		_schema->addSchema(name, index, GFT_INTEGER);
		_values[index] = new QVariant(value);
	} 

	void setObject(QString name, int index, const QVariant &value)
	{
		_schema->addSchema(name, index, GFT_OBJECT);
		_values[index] = new QVariant(value);
	}
	 
	void setValue(QString name, int index, eGeneralFieldType type, const QVariant &value)
	{ 
		switch (type)
		{
		case GFT_INTEGER:
			setInteger(name, index, value.toInt());
			break;
		case GFT_STRING:
			setString(name, index, value.toString());
			break;
		case GFT_GUID:
			//qDebug() << value.toUuid();
			setGuid(name, index,  value.toUuid());
			break;
		case GFT_OBJECT:
			setObject(name, index, value);
			break;
		case GFT_DOUBLE: 
			setInteger(name, index, value.toDouble());
			break;
		case GFT_BYTE:
			setByte(name, index, value.toByteArray());
			break;
		default:
			break;
		}
	}

	GeneralSchema *getSchema()
	{
		return _schema;
	}

	QMap<int, QVariant*> getValues()
	{
		return _values;
	}

protected:

	GeneralSchema *_schema;
	QMap<int,QVariant*> _values;
};  
   