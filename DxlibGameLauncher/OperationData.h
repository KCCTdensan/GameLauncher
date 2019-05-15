#pragma once

#include <string>
#include "SceneManager.h"

#ifdef UNICODE

using tstring = std::wstring;

#else

using tstring = std::string;

#endif

namespace Ope {

	extern int CURRENT_WINDOW_SIZE_X;
	extern int CURRENT_WINDOW_SIZE_Y;
	extern int CURRENT_WINDOW_COLOR_BIT;

	extern float WINDOW_SIZE_RATE;
	extern float WINDOW_SIZE_RATE_TIME;

	extern HWND MAIN_WINDOW_HANDLE;

	extern SceneManager sceneManager;

}