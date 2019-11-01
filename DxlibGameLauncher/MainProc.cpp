#include "DxLib.h"
#include <Windows.h>
#include "OperationData.h"
#include "AppData.h"
#include "ObjectManager.h"
#include "SceneManager.hpp"
#include "HEADER_Scene.h"
#include "InputManager.h"
#include "ExePath.h"
#include "MusicManager.h"
#include "JsonFileData.h"

int Ope::CURRENT_WINDOW_COLOR_BIT = 0;
int Ope::CURRENT_WINDOW_SIZE_X = 0;
int Ope::CURRENT_WINDOW_SIZE_Y = 0;

float Ope::WINDOW_SIZE_RATE = 1.0f;
float Ope::WINDOW_SIZE_RATE_TIME = 1.0f;

bool Ope::SCENE_CHANGE_FLAG = FALSE;
SCENE Ope::SCENE_CHANGE_NUM = SCENE::TAB_HOME;

int Ope::HOME_BUTTON_NUM = 0;
int Ope::APP_BUTTON_NUM = 0;
int Ope::GAME_BUTTON_NUM = 0;
int Ope::MODEL_BUTTON_NUM = 0;
int Ope::MUSIC_BUTTON_NUM = 0;
int Ope::VIDEO_BUTTON_NUM = 0;
int Ope::OTHERS_BUTTON_NUM = 0;

bool Ope::JSON_MUSIC_FLAG = FALSE;
bool Ope::JSON_VIDEO_FLAG = FALSE;
bool Ope::JSON_PICTURE_FLAG = FALSE;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	HWND MAIN_WINDOW_HANDLE = GetMainWindowHandle();

	SetAlwaysRunFlag(TRUE);
	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(TRUE);//ウインドウ可変変更
	SetUseDirectInputFlag(TRUE);

	ExePath exePath;

	SetWindowText(L"GameLauncher");

	SetDrawArea(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y);

	if (DxLib_Init() == -1)
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
	SetWindowSize(960, 540);

	SetMouseDispFlag(TRUE);

	static ObjectManager objectManager;
	static MusicManager musicManager;

	Json NOW_ACTIVE_JSON;

	//******************************************************************

	//必要最低限のフォントハンドル作成

	objectManager.HandleFontSet(L"G50", OBJECT_FONT_GOTHIC, 50);//ヘッダーに必要
	objectManager.HandleFontSet(L"G30", OBJECT_FONT_GOTHIC, 30);//PlayingNotice必要
	//objectManager.HandleFontSet(L"G20", OBJECT_FONT_GOTHIC, 20);//一覧したの文字 

	//******************************************************************

	SceneManager sceneManager(objectManager, NOW_ACTIVE_JSON);

	sceneManager.ChanegeScene(SCENE::TAB_HOME);//初回起動はホーム

	HEADER_Scene headerScene(objectManager, musicManager, NOW_ACTIVE_JSON);

	while (!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen())
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