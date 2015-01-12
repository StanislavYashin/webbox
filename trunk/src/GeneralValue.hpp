#pragma once

#include <qvariant.h>

class GeneralValue : public QVariant
{
public :
	GeneralValue(const GeneralValue& value)
		:QVariant(value)
	{ 
	}

//public:
//	GeneralValue(void *obj)
//	{
//		object = obj;
//	}
//
//	void setObject(void *obj)
//	{
//		object = obj;
//	}
//
//	void *getObject()
//	{
//		return object;
//	}
//private: 
//	void *object;
};
 
 