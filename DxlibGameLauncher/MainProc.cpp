#include "DxLib.h"
#include <Windows.h>
#include "OperationData.h"
#include "AppData.h"


int Ope::CURRENT_WINDOW_COLOR_BIT = 0;
int Ope::CURRENT_WINDOW_SIZE_X = 0;
int Ope::CURRENT_WINDOW_SIZE_Y = 0;

float Ope::WINDOW_SIZE_RATE = 1.0f;
float Ope::WINDOW_SIZE_RATE_TIME = 1.0f;

HWND Ope::MAIN_WINDOW_HANDLE = (HWND)-1;

SceneManager Ope::sceneManager;
ObjectManager Ope::objectManager;

#pragma warning(push)
#pragma warning(disable:28251)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	Ope::MAIN_WINDOW_HANDLE = GetMainWindowHandle();

	SetAlwaysRunFlag(TRUE);
	ChangeWindowMode(FALSE);

	SetWindowText(TEXT("GameLauncher"));

	SetDrawArea(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y);


	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	Ope::sceneManager.ChanegeScene(TAB_HOME);//初回起動はホーム


	while (!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen())
	{
		Ope::sceneManager.Update();

		SetDrawScreen(DX_SCREEN_BACK);
		Ope::sceneManager.Draw();

	}
	DxLib_End();
	return 0;				// ソフトの終了 
}
#pragma warning(pop)