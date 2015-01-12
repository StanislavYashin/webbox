#pragma once

#include "WebTask.hpp"
#include <qstring.h>

class HttpTask : public WebTask
{
public:
	QString url;
};