#pragma once

#include <qstring.h>
#include <qdir.h>
#include "PathUtil.h"

#define CACHE_DIR	L"Cache"
#define PROFILE_DIR L"Profile"
#define UPDATE_DIR	L"Update"
#define CONFIG_DIR	L"Config"
#define ICON_DIR	L"Icons"
#define COVER_DIR	L"Covers"
#define MAIN_DB		L"main.db"

namespace Webbox
{
namespace Config
{
class AllCfg
{
public:

	static QString joinPath(QString arg0,QString arg1)
	{
		QString basePath = Utility::PathUtil::GetCurrentExePath();
		return QString("%1\\%2\\%3\\").arg(basePath, arg0 , arg1);
	}

	static QString getCoverPath()
	{ 
		QString path = joinPath(QString::fromWCharArray(CACHE_DIR), QString::fromWCharArray(COVER_DIR));
		if (!QDir(path).exists(path))
			QDir().mkpath(path);
				 
		return path;
	}

	static QString getIconPath()
	{
		QString path = joinPath(QString::fromWCharArray(CACHE_DIR), QString::fromWCharArray(ICON_DIR));
		if (!QDir(path).exists(path))
			QDir().mkpath(path); 

		return path;
	}
};
}
}

