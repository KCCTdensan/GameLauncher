#include "DxLib.h"
#include <Windows.h>
#include "ExePath.h"
#include "ApplicationPreference.h"
#include "SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) // windows�ɒ�`���ꂽ�֐� ���C���s��
{
	const HWND MAIN_WINDOW_HANDLE = GetMainWindowHandle(); // �E�C���h�E�n���h���擾 ���C���s��

	SetAlwaysRunFlag(TRUE); // ��ʂ�Active�łȂ��Ƃ��ɂ����s���邩�B���y�Đ��̂��ߊ�{��TRUE
	ChangeWindowMode(TRUE); // ��ʂ��E�C���h�E�ɂ��邩�BTRUE:�E�C���h�E FALSE:�S��ʁi�������C�S��ʂ͕`�悪�x���B�ʂ̕`��̎d���ł���Ă��܂����߁B)
	SetWindowSizeChangeEnableFlag(TRUE);// �E�C���h�E���ςɂ��邩TRUE�ŉ�
	SetUseDirectInputFlag(TRUE); // �C���v�b�g�̃I�u�W�F�N�g�Ń_�C���N�g�C���v�b�g���g�p���邩�ǂ����B��{��TRUE�̕����]�܂����B

	ExePath exePath; //���݂̃J�����g�f�B���N�g�����擾�ݒ肷�邽�߂̃N���X�̕ϐ��錾 ���C���s��

	SetWindowText("GameLauncher"); // �A�v���̃^�C�g�����̕ύX

	if (DxLib_Init() == -1) // Dxlib������ �I���̌ザ��Ȃ��ƁC�摜�E�t�H���g�n���h�������`�摀�삪�����Ȃ�
	{
		return -1; // ���������s�̏ꍇ�͏I�� ����{�͖��Ȃ�
	}

#if _DEBUG // DEBUG�̎��̐錾 �����_�œ��ɋL�q�͂Ȃ�
	// .vcxproj�̃f�B���N�g���ɕ��荞��
#else
	SetCurrentDirectory(exePath.GetPath());//������ɂ���������Copy&Paste
#endif

	SetMouseDispFlag(TRUE); // �}�E�X��\�����邩�B�S��ʂł̓f�t�H�ł͕\������Ȃ�����

	SetWindowStyleMode(1); // �{�[�_���X�E�C���h�E

	SetWindowInitPosition(0, 0); // �E�C���h�E�̏ꏊ��ݒ蓮��m�F�ł͋@�\���Ă��Ȃ�

	SetDrawMode(DX_DRAWMODE_ANISOTROPIC);

	SetDrawArea(0, 0, (int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y);

	SceneManager sceneManager;

	while (!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen()) // ���C�����[�v ���̒��̏����͂Ȃ��ƃo�O�����
	{
		sceneManager.Update();
		sceneManager.Draw();
		if (CheckHitKeyAll()) break;
	}

	DxLib_End();
	return 0;
}