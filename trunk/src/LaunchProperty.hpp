#pragma once

#include "stdafx.h"
#include "CommonProperty.hpp"

namespace Webbox
{
	namespace Data
	{
		struct LaunchProperty : public CommonProperty
		{
			QString icon_name;
			QString name_cn;
			//get icon from db(to be implemented)
			//temporary method
			/*virtual QString GetIconPath() const
			{
				return Config::AllCfg::getIconPath() + icon;
			}*/
		};
	}
}