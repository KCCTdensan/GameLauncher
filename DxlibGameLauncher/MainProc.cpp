#include "OperationData.h"
#include "AppData.h"


int Ope::CURRENT_WINDOW_COLOR_BIT = 0;
int Ope::CURRENT_WINDOW_SIZE_X = 0;
int Ope::CURRENT_WINDOW_SIZE_Y = 0;

SceneManager Ope::sceneManager;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetAlwaysRunFlag(TRUE);
	ChangeWindowMode(FALSE);

	SetWindowText(TEXT("GameLauncher"));

	SetDrawArea(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y);
	
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	while (!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen())
	{
		SetDrawScreen(DX_SCREEN_BACK);
	}

	DxLib_End();

	return 0;
}