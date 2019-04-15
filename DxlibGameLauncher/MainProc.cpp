#include "DxLib.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if(DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	while(!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen())
	{
		SetDrawScreen(DX_SCREEN_BACK);

	}

	return 0;				// ソフトの終了 
}