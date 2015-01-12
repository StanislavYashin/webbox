#pragma once

#include "AtomReader.hpp"
#include "GeneralInstance.hpp"
#include "AllCfg.h"
#include "SchemaHelper.h"

class GeneralDocument
{
public:
	
	/*
	static GeneralDocument &instance()
	{
		static GeneralDocument provider;
		return provider; 
	}*/
 
	GeneralInstance *getInstanceByIndex(int index)
	{
		if (index >= 0 && index< __instanceList.count())
			return __instanceList.at(index);
		return NULL;
	}

	GeneralInstance *getInstanceByName(QString name)
	{
		for (int i = 0; i < __instanceList.count(); ++i)
		{
			int idx = __instanceList.at(i)->getIndexByName(name);
			if (idx != -1)
				return getInstanceByIndex(idx);
		}

		return NULL;
	}

	QList<GeneralInstance *> findProperty(QString fieldName, QVariant *value)
	{
		QList<GeneralInstance *> instanceList;

		for (int i = 0; i < __instanceList.count(); ++i)
		{
			GeneralInstance *inst = __instanceList.at(i);
			QVariant *instvalue = inst->getValue(fieldName);
			if (*instvalue == *value)
				instanceList.append(__instanceList.at(i));
		}

		return instanceList;
	}

public:

	GeneralDocument(QString dbName,QString tableName,GeneralSchema *schema)
	{ 
		reader = new AtomReader();
		load(dbName,tableName,schema);
	} 

	virtual ~GeneralDocument()
	{
		delete reader;
	}

	void load(QString dbName,QString tableName, GeneralSchema *schema)
	{ 
		__instanceList = reader->readFromDb(dbName, tableName, schema);
	}

private:

	QList<GeneralInstance*> __instanceList;

	AtomReader *reader;
};