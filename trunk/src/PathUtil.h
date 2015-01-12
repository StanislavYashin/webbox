#pragma once

#include <qstring.h>
#include <qapplication.h>

namespace Webbox
{
	namespace Utility
	{
		class PathUtil
		{
		public:
			//use qt method to get current app dir
			static QString GetCurrentExePath()
			{ 
				return QCoreApplication::applicationDirPath();
			}
		};
	}
}