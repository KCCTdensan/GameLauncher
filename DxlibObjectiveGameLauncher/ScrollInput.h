#pragma once
#include "DxLib.h"

namespace Input {
	class ScrollInput
	{
	public:
		static void Update();

		static int scrollSize;
	};
}

int Input::ScrollInput::scrollSize = 0;