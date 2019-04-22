#include "DxLib.h"
#include "OperationData.h"
#include <Windows.h>

int Ope::CURRENT_WINDOW_COLOR_BIT = 0;
int Ope::CURRENT_WINDOW_SIZE_X = 0;
int Ope::CURRENT_WINDOW_SIZE_Y = 0;

SceneManager Ope::sceneManager;

#pragma warning(push)
#pragma warning(disable:28251)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetAlwaysRunFlag(TRUE);
	ChangeWindowMode(FALSE);
	SetWindowSize();

		SetWindowText("a");

	if(DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}



	while(!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen())
	{
		SetDrawScreen(DX_SCREEN_BACK);

	}
	DxLib_End();
	return 0;				// ソフトの終了 
}
#pragma warning(pop)