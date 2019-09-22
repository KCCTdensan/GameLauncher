#include "DxLib.h"
#include <Windows.h>
//#include "OperationData.h"
#include "AppData.h"
#include "ObjectManager.h"
#include "scene_manager.hpp"

/*
int Ope::CURRENT_WINDOW_COLOR_BIT = 0;
int Ope::CURRENT_WINDOW_SIZE_X = 0;
int Ope::CURRENT_WINDOW_SIZE_Y = 0;

float Ope::WINDOW_SIZE_RATE = 1.0f;
float Ope::WINDOW_SIZE_RATE_TIME = 1.0f;
*/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//HWND mainWindowHandle = GetMainWindowHandle();
	static ObjectManager objectManager;

	SetAlwaysRunFlag(TRUE);
	ChangeWindowMode(FALSE);

	SetWindowText(L"GameLauncher");

	SetDrawArea(0, 0, App::BackgroundSize.width, App::BackgroundSize.height);

	if(DxLib_Init() == -1)
	{
		return -1;
	}

	SceneManager sceneManager(objectManager);

	while(!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen())
	{
		sceneManager.update();

		SetDrawScreen(DX_SCREEN_BACK);
		sceneManager.draw();
	}

	DxLib_End();

	return 0;
}