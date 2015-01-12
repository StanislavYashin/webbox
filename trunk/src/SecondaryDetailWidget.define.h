#pragma once

#include <QtWidgets>

struct DetailGameInfo
{
	QString title_zh;
	QString title_en;
	QString publisher;
	QString platform;
	QString rating;
	QString type;
	QString date;

	DetailGameInfo()
		:title_zh(""), title_en(""), publisher(""), platform(""), rating(""), type(""), date("")
	{ 
	}
};