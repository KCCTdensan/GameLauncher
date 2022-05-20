#include "DxLib.h"
#include <Windows.h>
#include <thread>
#include <future>
#include <chrono>
#include <string>
#include <iostream>
#include "ExePath.h"
#include "ApplicationPreference.h"
#include "MouseInput.h"
#include "SceneManager.h"
#include "MainThreadValue.h"
#include "WindowHolding.h"
#include "DebugScene.h"

/*void InputUpdate(); // threadA
void ApplicationUpdate(SceneManager* _sceneManager); // threadB*/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) // windows�ɒ�`���ꂽ�֐� ���C���s��
{
#if _DEBUG // DEBUG�̎��̐錾 �����_�œ��ɋL�q�͂Ȃ�
	// .vcxproj�̃f�B���N�g���ɕ��荞��
#else
	SetCurrentDirectory(exePath.GetPath());//������ɂ���������Copy&Paste
#endif

	const HWND MAIN_WINDOW_HANDLE = GetMainWindowHandle(); // �E�C���h�E�n���h���擾 ���C���s��

	SetMultiThreadFlag(TRUE); // �}���`�X���b�h�Ή�
	SetAlwaysRunFlag(TRUE); // ��ʂ�Active�łȂ��Ƃ��ɂ����s���邩�B���y�Đ��̂��ߊ�{��TRUE
	ChangeWindowMode(TRUE); // ��ʂ��E�C���h�E�ɂ��邩�BTRUE:�E�C���h�E FALSE:�S��ʁi�������C�S��ʂ͕`�悪�x���B�ʂ̕`��̎d���ł���Ă��܂����߁B)
	SetWindowSizeChangeEnableFlag(TRUE);// �E�C���h�E���ςɂ��邩TRUE�ŉ�
	SetUseDirectInputFlag(FALSE); // �C���v�b�g�̃I�u�W�F�N�g�Ń_�C���N�g�C���v�b�g���g�p���邩�ǂ����B��{��TRUE�̕����]�܂����B

	ExePath exePath; //���݂̃J�����g�f�B���N�g�����擾�ݒ肷�邽�߂̃N���X�̕ϐ��錾 ���C���s��

	SetWindowText("GameLauncher"); // �A�v���̃^�C�g�����̕ύX

	SetWindowStyleMode(1); // �{�[�_���X�E�C���h�E

	SetGraphMode((int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y, 32);

	if (DxLib_Init() == -1) // Dxlib������ �I���̌ザ��Ȃ��ƁC�摜�E�t�H���g�n���h�������`�摀�삪�����Ȃ�
	{
		return -1; // ���������s�̏ꍇ�͏I�� ����{�͖��Ȃ�
	}

	MSG msg;

	PosVec monitorSize((float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN));

	SetMouseDispFlag(TRUE); // �}�E�X��\�����邩�B�S��ʂł̓f�t�H�ł͕\������Ȃ�����

	SetWindowInitPosition(0, 0); // �E�C���h�E�̏ꏊ��ݒ蓮��m�F�ł͋@�\���Ă��Ȃ�

	SetDrawMode(DX_DRAWMODE_ANISOTROPIC);

	SetDrawArea(0, 0, (int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y);

	SetWindowSize((int)(monitorSize.x) * 4 / 5, (int)monitorSize.y * 4 / 5);
	SetWindowMinSize((int)(monitorSize.x) / 4, (int)(monitorSize.y) / 4);

	//SceneManager::AddScene("debug", new DebugScene());
	SceneManager::Initialize();

	SceneManager::ChangeScene("debug", new DebugScene(), false);

	//std::thread inputUpdate(InputUpdate);
	//std::thread applicationUpdate(ApplicationUpdate, &sceneManager);

	while (!ScreenFlip() && !ClearDrawScreen() && !MainThread::SetEnd()) // ���C�����[�v ���̒��̏����͂Ȃ��ƃo�O�����
	{
		GetMessage(&msg, NULL, 0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		WindowHolding::Update();
		SetDrawScreen(DX_SCREEN_BACK);
		Input::MouseInput::Update();
		SceneManager::Update();
		SceneManager::Draw();

		// �ǂ����ɃN���X�����ڂ� debug
		if (Input::MouseInput::GetClick(MOUSE_INPUT_5) == PressFrame::FIRST)
			SceneManager::ChangeSceneForward();
		if (Input::MouseInput::GetClick(MOUSE_INPUT_4) == PressFrame::FIRST)
			SceneManager::ChangeSceneBackward();

		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			MainThread::SetEnd(true);
			break;
		}
	}

	//inputUpdate.join();
	//applicationUpdate.join();

	DxLib_End();
	return 0;
}

/*void InputUpdate() {
	while (!MainThread::SetEnd()) {

		Input::MouseInput::Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void ApplicationUpdate(SceneManager* _sceneManager) {
	while (!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen() && !MainThread::SetEnd()) // ���C�����[�v ���̒��̏����͂Ȃ��ƃo�O�����
	{
		_sceneManager->Update(); // ���[�v���Ōp�����Ďg�p�C�w�b�_�[�͂��ꂼ��ŃC���X�^���X�����Ă�������
		_sceneManager->Draw();

		std::string tmp = std::to_string(Input::MouseInput::GetMouse().x);
		std::string tmp2 = std::to_string(Input::MouseInput::GetMouse().y);
		DrawString(500, 500, tmp.c_str(), GetColor(255, 255, 255));
	}
}*/