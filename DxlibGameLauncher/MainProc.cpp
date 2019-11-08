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
#include "JsonManager.h"

/*################ �O���[�o���ϐ��̒�`�ꏊ ##################*/

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

/*############################################################*/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) // windows�ɒ�`���ꂽ�֐� ���C���s��
{
	HWND MAIN_WINDOW_HANDLE = GetMainWindowHandle(); // �E�C���h�E�n���h���擾 ���C���s��

	SetAlwaysRunFlag(TRUE); // ��ʂ�Active�łȂ��Ƃ��ɂ����s���邩�B���y�Đ��̂��ߊ�{��TRUE
	ChangeWindowMode(TRUE); // ��ʂ��E�C���h�E�ɂ��邩�BTRUE:�E�C���h�E FALSE:�S��ʁi�������C�S��ʂ͕`�悪�x���B�ʂ̕`��̎d���ł���Ă��܂����߁B)
	SetWindowSizeChangeEnableFlag(TRUE);// �E�C���h�E���ςɂ��邩TRUE�ŉ�
	SetUseDirectInputFlag(TRUE); // �C���v�b�g�̃I�u�W�F�N�g�Ń_�C���N�g�C���v�b�g���g�p���邩�ǂ����B��{��TRUE�̕����]�܂����B

	ExePath exePath; //���݂̃J�����g�f�B���N�g�����擾�ݒ肷�邽�߂̃N���X�̕ϐ��錾 ���C���s��

	SetWindowText("GameLauncher"); // �A�v���̃^�C�g�����̕ύX

	SetDrawArea(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y); // �`��̈�̐ݒ� ���� ���̒��ł��`��ł���͈͂�ݒ� ����Ɋւ��Ă͂��܂�g��Ȃ��������� (����͕\��ʂł͂Ȃ�����ʂȂ̂ł��̉�ʂŐݒ肵���T�C�Y��\��ʂŃ��T�C�Y����

	if (DxLib_Init() == -1) // Dxlib������ �I���̌ザ��Ȃ��ƁC�摜�E�t�H���g�n���h�������`�摀�삪�����Ȃ�
	{
		return -1; // ���������s�̏ꍇ�͏I�� ����{�͖��Ȃ�
	}

#if _DEBUG // DEBUG�̎��̐錾 �����_�œ��ɋL�q�͂Ȃ�
	// .vcxproj�̃f�B���N�g���ɕ��荞��
#else
	SetCurrentDirectory(exePath.GetPath());//������ɂ���������Copy&Paste
#endif

	SetGraphMode(App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y, 32); // ��������`��̈�̐ݒ�

	SetMouseDispFlag(TRUE); // �}�E�X��\�����邩�B�S��ʂł̓f�t�H�ł͕\������Ȃ�����

	static ObjectManager objectManager; // �����`���[�̃��C���ł���object��z�u���邽�߂̋��ʂ̕ϐ�
	static MusicManager musicManager; // �w�b�_�[�ŊǗ����鉹�y�̊Ǘ��ϐ�

	static Json NOW_ACTIVE_JSON;

	static JsonManager jsonManager;
	jsonManager.Read(".\\Content\\Json\\data.json");

	//******************************************************************

	//�K�v�Œ���̃t�H���g�n���h���쐬

	objectManager.HandleFontSet("G50", OBJECT_FONT_GOTHIC, 50);//�w�b�_�[�ɕK�v
	objectManager.HandleFontSet("G30", OBJECT_FONT_GOTHIC, 30);//PlayingNotice�K�v
	objectManager.HandleFontSet("G20", OBJECT_FONT_GOTHIC, 20);//�ꗗ�����̕��� 

	//******************************************************************

	SceneManager sceneManager(objectManager, NOW_ACTIVE_JSON, jsonManager); // json�őI�𒆂̂��̂��擾������̂���荞��ł��� ���CSceneManager�̒�`

	sceneManager.ChanegeScene(SCENE::TAB_HOME);//����N���̓z�[��

	HEADER_Scene headerScene(objectManager, musicManager, NOW_ACTIVE_JSON, jsonManager);

	SetWindowSize(App::DEFAULT_WINDOW_SIZE_X * 4 / 5, App::DEFAULT_WINDOW_SIZE_Y * 4 / 5); // �����̃E�C���h�E�T�C�Y 1920 * 1080 ��z��

	SetWindowInitPosition(0, 0); // �E�C���h�E�̏ꏊ��ݒ蓮��m�F�ł͋@�\���Ă��Ȃ�

	SetDrawMode(DX_DRAWMODE_ANISOTROPIC);

	while (!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen()) // ���C�����[�v ���̒��̏����͂Ȃ��ƃo�O�����
	{

		// �������֌W

		Input::Mouse::Update();
		Input::KeyBoard::Update();

		objectManager.Update();
		sceneManager.Update();
		headerScene.Update();

		SetDrawScreen(DX_SCREEN_BACK); // ����ʕ`��ݒ�

		// ���`��֌W

		sceneManager.Draw();
		headerScene.Draw();
		objectManager.Draw();

		if (Ope::SCENE_CHANGE_FLAG) // ���ꂪTRUE�̎��V�[�����؂�ւ��
		{
			sceneManager.ChanegeScene(Ope::SCENE_CHANGE_NUM);
		}

		//if (Input::KeyBoard::KEY[KEY_INPUT_ESCAPE] == KEYBOARD_PRESS_FIRST) { // Esc���������ƂŏI������@�\ �딚�������炵���̂ŃR�����g�A�E�g
			//break;
		//}
	}

	DxLib_End(); // Dxlib�I��
	return 0;
}