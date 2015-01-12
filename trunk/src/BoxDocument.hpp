#pragma once

#include "GeneralDocument.hpp"
#include "CommonProperty.hpp"
#include <qvariant.h>

using namespace Webbox;

class BoxDocument : public GeneralDocument
{
public:
	BoxDocument(QString dbName, QString tableName, GeneralSchema *schema)
		:GeneralDocument(dbName,tableName,schema)
	{
	}

	Data::CommonProperty *getProperty(int index)
	{
		return (Webbox::Data::CommonProperty *)getInstanceByIndex(index);
	}

	Data::CommonProperty *getProperty(QString fieldName)
	{
		return (Data::CommonProperty *)getInstanceByName(fieldName);
	}
	
	QList<Data::CommonProperty*> findCategory(QString category)
	{
		auto instanceList = findProperty("category", &QVariant(category));
		QList<Data::CommonProperty*> ret;
		for (int i = 0; i < instanceList.count(); ++i)
		{
			ret.append((Data::CommonProperty*)instanceList.at(i));
		}
		return ret;
	}
};