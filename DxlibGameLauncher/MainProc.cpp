#include "DxLib.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if(DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	while(!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen())
	{
		SetDrawScreen(DX_SCREEN_BACK);

	}

	return 0;				// �\�t�g�̏I�� 
}