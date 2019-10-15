#include "DxLib.h"
#include <Windows.h>
#include "OperationData.h"
#include "AppData.h"
#include "ObjectManager.h"
#include "SceneManager.hpp"


int Ope::CURRENT_WINDOW_COLOR_BIT = 0;
int Ope::CURRENT_WINDOW_SIZE_X = 0;
int Ope::CURRENT_WINDOW_SIZE_Y = 0;

float Ope::WINDOW_SIZE_RATE = 1.0f;
float Ope::WINDOW_SIZE_RATE_TIME = 1.0f;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	static ObjectManager objectManager;
	SceneManager sceneManager(objectManager);
	HWND MAIN_WINDOW_HANDLE = GetMainWindowHandle();

	SetAlwaysRunFlag(TRUE);
	ChangeWindowMode(false);
	SetWindowSizeChangeEnableFlag(TRUE);//ウインドウ可変変更
	SetUseDirectInputFlag(TRUE);

	SetWindowText(L"GameLauncher");

	SetDrawArea(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y);

	if(DxLib_Init() == -1)
	{
		return -1;
	}

	sceneManager.ChanegeScene(TAB_HOME);//初回起動はホーム

	while(!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen())
	{
		sceneManager.Update();

		SetDrawScreen(DX_SCREEN_BACK);
		sceneManager.Draw();
	}
	DxLib_End();
	return 0;
}