#include "WindowManager.h"
#include "OperationData.h"
#include "AppData.h"
#include "InputManager.h"
#include "DxLib.h"
//#include <Windows.h>


void WindowManager::Update(HWND mainWindowHandle)
{
	/*RECT rec;
	GetClientRect(mainWindowHandle, &rec);
	Ope::CURRENT_WINDOW_SIZE_X = rec.right - rec.left;
	Ope::CURRENT_WINDOW_SIZE_Y = rec.bottom - rec.top;

	Ope::WINDOW_SIZE_RATE = 1.0f * Ope::CURRENT_WINDOW_SIZE_X / App::BACKGROUND_SIZE_X;
	Ope::WINDOW_SIZE_RATE_TIME = 1.0f * App::BACKGROUND_SIZE_Y / Ope::CURRENT_WINDOW_SIZE_Y;*/

	if (Input::KeyBoard::KEY[KEY_INPUT_F11] == KEYBOARD_PRESS_FIRST) {
		if(!Ope::WINDOWS_FULLSCREEN) {
			Ope::WINDOWS_FULLSCREEN = TRUE;
			SetWindowSize(App::DEFAULT_WINDOW_SIZE_X, App::DEFAULT_WINDOW_SIZE_Y); // 初期のウインドウサイズ 1920 * 1080 を想定
		}
		else {
			Ope::WINDOWS_FULLSCREEN = FALSE;
			SetWindowSize(App::DEFAULT_WINDOW_SIZE_X * 4 / 5, App::DEFAULT_WINDOW_SIZE_Y * 4 / 5); // 初期のウインドウサイズ 1920 * 1080 を想定
		}
	}
}