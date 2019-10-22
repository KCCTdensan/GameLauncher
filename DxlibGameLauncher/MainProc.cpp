#include "DxLib.h"
#include <Windows.h>
#include "OperationData.h"
#include "AppData.h"
#include "ObjectManager.h"
#include "SceneManager.hpp"
#include "HEADER_Scene.h"
#include "InputManager.h"
#include "ExePath.h"


int Ope::CURRENT_WINDOW_COLOR_BIT = 0;
int Ope::CURRENT_WINDOW_SIZE_X = 0;
int Ope::CURRENT_WINDOW_SIZE_Y = 0;

float Ope::WINDOW_SIZE_RATE = 1.0f;
float Ope::WINDOW_SIZE_RATE_TIME = 1.0f;

bool Ope::SCENE_CHANGE_FLAG = FALSE;
SCENE Ope::SCENE_CHANGE_NUM = TAB_HOME;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	static ObjectManager objectManager;
	SceneManager sceneManager(objectManager);
	ExePath exePath;
	
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

#if _DEBUG
	// .vcxprojのディレクトリに放り込む
#else
	SetCurrentDirectory(exePath.GetPath());//こちらにも完成時にCopy&Paste
#endif

	SetGraphMode(App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y, 32);

	//SetWindowSize(App::DEFAULT_WINDOW_SIZE_X, App::DEFAULT_WINDOW_SIZE_Y);
	SetWindowSize(960,540);

	SetMouseDispFlag(TRUE);

	//******************************************************************

	//必要最低限のフォントハンドル作成

	objectManager.HandleFontSet(L"G50", OBJECT_FONT_GOTHIC, 50);//ヘッダーに必要
	objectManager.HandleFontSet(L"G20", OBJECT_FONT_GOTHIC, 20);//一覧したの文字

	//******************************************************************



	sceneManager.ChanegeScene(TAB_HOME);//初回起動はホーム

	HEADER_Scene headerScene(objectManager);

	while(!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen())
	{

		Input::Mouse::Update();
		Input::KeyBoard::Update();

		objectManager.Update();
		sceneManager.Update();
		headerScene.Update();

		SetDrawScreen(DX_SCREEN_BACK);
		
		sceneManager.Draw();
		headerScene.Draw();
		objectManager.Draw();

		if (Ope::SCENE_CHANGE_FLAG)
		{
			sceneManager.ChanegeScene(Ope::SCENE_CHANGE_NUM);
		}

		if (Input::KeyBoard::KEY[KEY_INPUT_ESCAPE] == KEYBOARD_PRESS_FIRST) {
			break;
		}
	}

	DxLib_End();
	return 0;
}