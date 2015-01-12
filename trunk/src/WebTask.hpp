#pragma once

#include <qstring.h>

enum eWebTaskType
{
	WT_TORRENT,
	WT_MAGNET,
	WT_HTTP,
	WT_HTTPS
};

enum eTaskPreviledge
{
	TP_HIGHEST=0,
	TP_HIGH,
	TP_NORMAL,
	TP_LOW,
	TP_LOWEST
};

class WebTask
{
public:

	eTaskPreviledge previledge;
	eWebTaskType type; 
	QString localpath;

public:

	void setPreviledge(eTaskPreviledge _prv)
	{
		previledge = _prv;
	}

	void setType(eWebTaskType _type)
	{
		type = type;
	}

	void setDownloadPath(QString _path)
	{
		localpath = _path;
	}
};