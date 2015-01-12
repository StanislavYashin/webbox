#pragma once
 
#include "GamePropertySimple.hpp"
#include <qlist.h>

namespace Webbox
{
	namespace Data
	{
		class GamePropertyComplete : public GamePropertySimple
		{
			QString desc;
			QString ver_info;

			QList<QString> snapshot_path;

		public:

			virtual QString GetIconPath() const
			{
				return GamePropertySimple::GetIconPath(); 
			}
		};
	}
}

