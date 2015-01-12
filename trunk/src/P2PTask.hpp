#pragma once

#include "WebTask.hpp"
#include <qbytearray.h>

class P2PTask : public WebTask
{
public:
	QByteArray torrent;
};