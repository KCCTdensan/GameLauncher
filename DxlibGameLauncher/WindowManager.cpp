#include "WindowManager.h"
#include <Windows.h>
#include "OperationData.h"
#include "AppData.h"

WindowManager::WindowManager()
{
}


WindowManager::~WindowManager()
{
}

void WindowManager::Update()
{
	RECT rec;
	GetClientRect(Ope::MAIN_WINDOW_HANDLE, &rec);
	Ope::CURRENT_WINDOW_SIZE_X = rec.right - rec.left;
	Ope::CURRENT_WINDOW_SIZE_Y = rec.bottom - rec.top;

	Ope::WINDOW_SIZE_RATE = Ope::CURRENT_WINDOW_SIZE_X / App::BACKGROUND_SIZE_X;
	Ope::WINDOW_SIZE_RATE_TIME = App::BACKGROUND_SIZE_Y / Ope::CURRENT_WINDOW_SIZE_Y;

}
