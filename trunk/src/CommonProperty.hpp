#pragma once

#include "stdafx.h"

#include <Windows.h>
#include <qstring.h>
#include "AllCfg.h"
#include "PathUtil.h"
#include "AtomReader.hpp"
#include <quuid.h>

#include "GeneralInstance.hpp"

#define P_GUID(name,field,index)\
	GUID get##name() {return getGuid(field);}\
	void set##name(GUID value) { setGuid(field,index,value);}

#define P_STRING(name,field,index)\
	QString get##name() {return getString(field);}\
	void set##name(QString value) { setString(field,index,value);}

#define P_INT(name,field,index)\
	int get##name() {return getInteger(field);}\
	void set##name(int value) { setInteger(field,index,value);}

#define P_BYTE(name,field,index)\
	QByteArray get##name() {return getByte(field);}\
	void set##name(QByteArray value) { setByte(field,index,value);}

namespace Webbox { 
namespace Data {
 
class CommonProperty : public GeneralInstance 
{
public: 
	CommonProperty()
		:GeneralInstance()
	{
	}

	CommonProperty(GeneralInstance *instance)
	{
		_schema = instance->getSchema();
		_values = instance->getValues(); 
	}
	
	P_GUID(Id, "id", 0);
	P_STRING(NameCN, "name_cn", 1);
	P_STRING(NameEn,"name_en",2);
	P_STRING(NameOther, "name_other", 3);
	P_STRING(Language, "language", 4);
	P_STRING(ReleaseDate, "release_date", 5);
	P_STRING(Company, "company", 6);
	P_STRING(Version, "version", 7);
	P_BYTE(Icon, "icon", 8);
	P_STRING(Homepage, "homepage", 9);
	P_STRING(Url, "url", 10);
	P_INT(Rank, "rank", 11);
	P_BYTE(Torrent, "torrent", 12);
	P_STRING(Magnet, "magnet", 13);
	P_STRING(BaiduYun, "baiduyun", 14);
	P_STRING(Size, "size", 15);
	P_INT(StarMarks, "star_marks", 16);
	P_STRING(Desc, "desc", 17);
	P_STRING(License, "license", 18);
	P_STRING(UpdateTime, "update_time", 19);
	P_STRING(SnapshotUrls, "snapshot_urls", 20);  
};
 
}
}