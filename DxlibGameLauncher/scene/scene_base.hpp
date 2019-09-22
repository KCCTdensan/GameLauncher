#pragma once

#include "../ObjectManager.h"


namespace scene
{
	class SceneBase
	{
	protected:
		ObjectManager &objectManager;

	public:
		SceneBase(ObjectManager &objectManager)
			:objectManager(objectManager)
		{

		}
		virtual void initialize()
		{

		}
		virtual void finalize()
		{

		}
		virtual void update()
		{
			objectManager.Update();
		}
		virtual void draw()
		{
			objectManager.Draw();
		}
	};
}