#pragma once

#include "scene_base.hpp"


namespace scene
{
	class TAB_HOME_Scene :
		public SceneBase
	{
	public:
		TAB_HOME_Scene(ObjectManager &objectManager);
		void initialize();
	};
}