#include "WindowManager.h"
#include "OperationData.h"
#include "AppData.h"
//#include <Windows.h>


void WindowManager::Update(HWND mainWindowHandle)
{
	RECT rec;
	GetClientRect(mainWindowHandle, &rec);
	Ope::CURRENT_WINDOW_SIZE_X = rec.right - rec.left;
	Ope::CURRENT_WINDOW_SIZE_Y = rec.bottom - rec.top;

	Ope::WINDOW_SIZE_RATE = 1.0f * Ope::CURRENT_WINDOW_SIZE_X / App::BackgroundSize.width;
	Ope::WINDOW_SIZE_RATE_TIME = 1.0f * App::BackgroundSize.height / Ope::CURRENT_WINDOW_SIZE_Y;
}