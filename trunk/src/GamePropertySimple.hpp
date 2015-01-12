#pragma once
 
#include "CommonProperty.hpp"
#include "GameProperty.define.h"

namespace Webbox 
{
	namespace Data
	{
		//appstore.db
		class GamePropertySimple : public CommonProperty
		{
		public:
			GamePropertySimple() : CommonProperty()
			{ 

			}

		protected:

			eGameType	  type;
			eGameCategory category;
			eGamePlatform platform;
 
		};
	}
}


