#include "DxLib.h"
#include <Windows.h>
#include "OperationData.h"
#include "AppData.h"
#include "ObjectManager.h"
#include "SceneManager.hpp"
#include "HEADER_Scene.h"


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
	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(TRUE);//ウインドウ可変変更
	SetUseDirectInputFlag(TRUE);

	SetWindowText(L"GameLauncher");

	SetDrawArea(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y);

	if(DxLib_Init() == -1)
	{
		return -1;
	}

	SetGraphMode(App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y, 32);

	//SetWindowSize(App::DEFAULT_WINDOW_SIZE_X, App::DEFAULT_WINDOW_SIZE_Y);
	SetWindowSize(960,540);

	SetMouseDispFlag(TRUE);

	sceneManager.ChanegeScene(TAB_HOME);//初回起動はホーム

	HEADER_Scene headerScene(objectManager);

	while(!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen())
	{

		objectManager.Update();
		sceneManager.Update();
		headerScene.Update();

		SetDrawScreen(DX_SCREEN_BACK);
		
		sceneManager.Draw();
		headerScene.Draw();
		objectManager.Draw();

		if (Input::KeyBoard::KEY[KEY_INPUT_ESCAPE] == KEYBOARD_PRESS_FIRST) {
			break;
		}
	}
	DxLib_End();
	return 0;
}