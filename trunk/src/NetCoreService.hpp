#pragma once

#include "HttpConfig.hpp"
#include "httpdownloadtask.h"
#include <boost/asio.hpp>  
#include <qlist.h>

class NetCoreService : public QObject
{
public:
	NetCoreService()
	{

	}
	virtual ~NetCoreService()
	{

	}

protected:

#ifdef USE_QTHTTP 
	QList<HttpDownloadTask *> taskQueue;
#elif USE_AVHTTP
	boost::asio::io_service _io; 
#endif

public:


};