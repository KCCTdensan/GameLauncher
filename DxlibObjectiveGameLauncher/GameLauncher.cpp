#include "DxLib.h"
#include <Windows.h>
#include <thread>
#include <future>
#include <chrono>
#include <string>
#include <iostream>
#include "ExePath.h"
#include "ApplicationPreference.h"
#include "ApplicationBuilder.h"
#include "MouseInput.h"
#include "SceneManager.h"
#include "MainThreadValue.h"
#include "DebugScene.h"
#include "ApplicationTime.h"
#include "AppClose.h"

/*void InputUpdate(); // threadA
void ApplicationUpdate(SceneManager* _sceneManager); // threadB*/

#define WM_NOTIFYICON (WM_USER + 100)

void GradX_RGB(int x1, int y1, int x2, int y2, BYTE r1, BYTE g1, BYTE b1, BYTE r2, BYTE g2, BYTE b2)
{
	VERTEX2D Vertex[6]{};

	Vertex[0].pos.x = (float)x1;
	Vertex[0].pos.y = (float)y1;
	Vertex[0].pos.z = 0.0f;
	Vertex[0].rhw = 1.0f;
	Vertex[0].dif.r = r1;
	Vertex[0].dif.g = g1;
	Vertex[0].dif.b = b1;
	Vertex[0].dif.a = 255;
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;

	Vertex[1].pos.x = (float)x2;
	Vertex[1].pos.y = (float)y1;
	Vertex[1].pos.z = 0.0f;
	Vertex[1].rhw = 1.0f;
	Vertex[1].dif.r = r2;
	Vertex[1].dif.g = g2;
	Vertex[1].dif.b = b2;
	Vertex[1].dif.a = 255;
	Vertex[1].u = 0.0f;
	Vertex[1].v = 0.0f;

	Vertex[2].pos.x = (float)x1;
	Vertex[2].pos.y = (float)y2;
	Vertex[2].pos.z = 0.0f;
	Vertex[2].rhw = 1.0f;
	Vertex[2].dif.r = r1;
	Vertex[2].dif.g = g1;
	Vertex[2].dif.b = b1;
	Vertex[2].dif.a = 255;
	Vertex[2].u = 0.0f;
	Vertex[2].v = 0.0f;

	Vertex[3].pos.x = (float)x2;
	Vertex[3].pos.y = (float)y2;
	Vertex[3].pos.z = 0.0f;
	Vertex[3].rhw = 1.0f;
	Vertex[3].dif.r = r2;
	Vertex[3].dif.g = g2;
	Vertex[3].dif.b = b2;
	Vertex[3].dif.a = 255;
	Vertex[3].u = 0.0f;
	Vertex[3].v = 0.0f;

	Vertex[4] = Vertex[2];

	Vertex[5] = Vertex[1];

	DrawPolygon2D(Vertex, 2, DX_NONE_GRAPH, FALSE);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) // windows�ɒ�`���ꂽ�֐� ���C���s��
{
	ExePath exePath; //���݂̃J�����g�f�B���N�g�����擾�ݒ肷�邽�߂̃N���X�̕ϐ��錾 ���C���s��
	SetOutApplicationLogValidFlag(FALSE);

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
	SetUseDirectInputFlag(TRUE); // �C���v�b�g�̃I�u�W�F�N�g�Ń_�C���N�g�C���v�b�g���g�p���邩�ǂ����B��{��TRUE�̕����]�܂����B
	SetMainWindowText("Launcher"); // �A�v���̃^�C�g�����̕ύX
	SetUseIMEFlag(TRUE);
	SetUseTSFFlag(FALSE);

	SetWindowStyleMode(11); // �{�[�_���X�E�C���h�E

	SetGraphMode((int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y, 32);

	SetBackgroundColor(20, 20, 20);

	//SetUseDirectInputFlag(FALSE);

	if (DxLib_Init() == -1) // Dxlib������ �I���̌ザ��Ȃ��ƁC�摜�E�t�H���g�n���h�������`�摀�삪�����Ȃ�
	{
		return -1; // ���������s�̏ꍇ�͏I�� ����{�͖��Ȃ�
	}

	ApplicationBuilder applicationBuilder;

	//MSG msg;

	PosVec monitorSize((float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN));

	SetMouseDispFlag(TRUE); // �}�E�X��\�����邩�B�S��ʂł̓f�t�H�ł͕\������Ȃ�����

	SetWindowInitPosition(0, 0); // �E�C���h�E�̏ꏊ��ݒ蓮��m�F�ł͋@�\���Ă��Ȃ�

	SetDrawMode(DX_DRAWMODE_ANISOTROPIC);

	SetDrawArea(0, 0, (int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y);

	SetWindowSize((int)(monitorSize.x) * 4 / 5, (int)monitorSize.y * 4 / 5);
	SetWindowMinSize((int)(monitorSize.x) / 4, (int)(monitorSize.y) / 4);

	SceneManager::Initialize();

	SceneManager::ChangeScene("debug", new DebugScene(), false); // �ŏ��ɕ\������y�[�W

	//std::thread inputUpdate(InputUpdate);
	//std::thread applicationUpdate(ApplicationUpdate, &sceneManager);

	COLORREF crCaption, crText;
	int cxFrame = GetSystemMetrics(SM_CXFRAME);
	int cyFrame = GetSystemMetrics(SM_CYFRAME);
	int cxButton = GetSystemMetrics(SM_CXSIZE);
	int cyButton = GetSystemMetrics(SM_CYSIZE);
	if (true) {
		crCaption = GetSysColor(COLOR_ACTIVECAPTION);
		crText = GetSysColor(COLOR_CAPTIONTEXT);
	}
	else {
		crCaption = GetSysColor(COLOR_INACTIVECAPTION);
		crText = GetSysColor(COLOR_INACTIVECAPTIONTEXT);
	}

	RECT rcWnd;
	char sz[128];
	GetWindowRect(GetMainWindowHandle(), &rcWnd);
	GetWindowText(GetMainWindowHandle(), sz, sizeof(sz) - 1);

	HDC	hdc = GetWindowDC(GetMainWindowHandle());

	//�e�L�X�g�`��̗�
	RECT rcFill;
	rcFill.left = cxFrame + cxButton + 1;
	rcFill.right = (rcWnd.right - rcWnd.left) - (cxFrame + 3 * (cxButton + 1));
	rcFill.top = cyFrame;
	rcFill.bottom = cyFrame + cyButton;
	SetTextColor(hdc, crText);
	SetBkColor(hdc, crCaption);
	HBRUSH hbr = CreateSolidBrush(crCaption);
	FillRect(hdc, &rcFill, hbr);
	DeleteObject(hbr);
	DrawText(hdc, sz, lstrlen(sz), &rcFill,
		DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

	DeleteDC(hdc);

	ReleaseDC(GetMainWindowHandle(), hdc);

	while (!ScreenFlip() && !ClearDrawScreen() && !MainThread::SetEnd()) // ���C�����[�v ���̒��̏����͂Ȃ��ƃo�O�����
	{		
		applicationBuilder.Update(); // �V�X�e���n�X�V����(���܂Ƃ߂��Ă���)
		//GetMessage(&msg, NULL, 0, 0);
		//TranslateMessage(&msg);
		//DispatchMessage(&msg); // �E�C���h�E���b�Z�[�W����
		ProcessMessage();

		SetDrawScreen(DX_SCREEN_BACK); // �`�揉����
		Input::MouseInput::Update(); // �}�E�X�X�V����

		SceneManager::Collide();
		SceneManager::Update();
		SceneManager::Draw(); // �V�[���X�V����

		//GradX_RGB(10, 200, 630, 280, 255, 128, 0, 0, 255, 128);

		SceneManager::UpdateForwardBackwardScene(
			Input::MouseInput::GetClick(MOUSE_INPUT_5), PressFrame::FIRST,
			Input::MouseInput::GetClick(MOUSE_INPUT_4), PressFrame::FIRST);

		if (/*CheckHitKey(KEY_INPUT_ESCAPE) ||*/ AppClose::GetClosed()) {
			MainThread::SetEnd(true);
			break;
		}

		/*std::string buf;
		char a[40] = "";

		KeyInputString(500, 500, 20, a, true);*/

		// debug
	}

	//inputUpdate.join();
	//applicationUpdate.join();

	DxLib_End(); // ���C�u����end
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