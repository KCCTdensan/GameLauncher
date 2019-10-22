#include "DxLib.h"
#include <Windows.h>
#include "OperationData.h"
#include "AppData.h"
#include "ObjectManager.h"
#include "SceneManager.hpp"
#include "HEADER_Scene.h"
#include "ExePath.h"
#include "input/keyboard.hpp"
#include "input/mouse.hpp"


int Ope::CURRENT_WINDOW_COLOR_BIT = 0;
int Ope::CURRENT_WINDOW_SIZE_X = 0;
int Ope::CURRENT_WINDOW_SIZE_Y = 0;

float Ope::WINDOW_SIZE_RATE = 1.0f;
float Ope::WINDOW_SIZE_RATE_TIME = 1.0f;

bool Ope::SCENE_CHANGE_FLAG = FALSE;
SCENE Ope::SCENE_CHANGE_NUM = TAB_HOME;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Size windowSize = {960,540};
	input::Keyboard keyboard;
	input::Mouse mouse(App::BackgroundSize, windowSize);
	static ObjectManager objectManager;
	SceneManager sceneManager(objectManager);
	ExePath exePath;
	
	HWND MAIN_WINDOW_HANDLE = GetMainWindowHandle();

	SetAlwaysRunFlag(TRUE);
	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(TRUE);//ウインドウ可変変更
	SetUseDirectInputFlag(TRUE);

	SetWindowText(L"GameLauncher");

	SetDrawArea(0, 0, App::BackgroundSize.width, App::BackgroundSize.height);

	if(DxLib_Init() == -1)
	{
		return -1;
	}

#if _DEBUG
	// .vcxprojのディレクトリに放り込む
#else
	SetCurrentDirectory(exePath.GetPath());//こちらにも完成時にCopy&Paste
#endif

	SetGraphMode(App::BackgroundSize.width, App::BackgroundSize.height, 32);

	//SetWindowSize(App::DEFAULT_WINDOW_SIZE_X, App::DEFAULT_WINDOW_SIZE_Y);
	SetWindowSize(windowSize.width, windowSize.height);

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
		keyboard.update();
		mouse.update();

		objectManager.Update(mouse.getCursorPosition(), mouse.getMouseButtonInput());
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
		if(keyboard.getPressStatus(KEY_INPUT_ESCAPE) == input::KeyPressID::KeyPressOnce)
		{
			break;
		}
	}

	DxLib_End();
	return 0;
}