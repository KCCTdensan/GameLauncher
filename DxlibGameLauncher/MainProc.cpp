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

/*################ グローバル変数の定義場所 ##################*/

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

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) // windowsに定義された関数 ※修正不可
{
	HWND MAIN_WINDOW_HANDLE = GetMainWindowHandle(); // ウインドウハンドル取得 ※修正不可

	SetAlwaysRunFlag(TRUE); // 画面がActiveでないときにも実行するか。音楽再生のため基本はTRUE
	ChangeWindowMode(TRUE); // 画面をウインドウにするか。TRUE:ウインドウ FALSE:全画面（ただし，全画面は描画が遅い。別の描画の仕方でされてしまうため。)
	SetWindowSizeChangeEnableFlag(TRUE);// ウインドウを可変にするかTRUEで可変
	SetUseDirectInputFlag(TRUE); // インプットのオブジェクトでダイレクトインプットを使用するかどうか。基本はTRUEの方が望ましい。

	ExePath exePath; //現在のカレントディレクトリを取得設定するためのクラスの変数宣言 ※修正不可

	SetWindowText("GameLauncher"); // アプリのタイトル名の変更

	SetDrawArea(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y); // 描画領域の設定 かつ その中でも描画できる範囲を設定 これに関してはあまり使わない方がいい (これは表画面ではなく裏画面なのでこの画面で設定したサイズを表画面でリサイズする

	if (DxLib_Init() == -1) // Dxlib初期化 ！この後じゃないと，画像・フォントハンドル操作や描画操作が動かない
	{
		return -1; // 初期化失敗の場合は終了 ※基本は問題ない
	}

#if _DEBUG // DEBUGの時の宣言 現時点で特に記述はなし
	// .vcxprojのディレクトリに放り込む
#else
	SetCurrentDirectory(exePath.GetPath());//こちらにも完成時にCopy&Paste
#endif

	SetGraphMode(App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y, 32); // こちらも描画領域の設定

	SetMouseDispFlag(TRUE); // マウスを表示するか。全画面ではデフォでは表示されないため

	static ObjectManager objectManager; // ランチャーのメインであるobjectを配置するための共通の変数
	static MusicManager musicManager; // ヘッダーで管理する音楽の管理変数

	static Json NOW_ACTIVE_JSON;

	static JsonManager jsonManager;
	jsonManager.Read(".\\Content\\Json\\data.json");

	//******************************************************************

	//必要最低限のフォントハンドル作成

	objectManager.HandleFontSet("G50", OBJECT_FONT_GOTHIC, 50);//ヘッダーに必要
	objectManager.HandleFontSet("G30", OBJECT_FONT_GOTHIC, 30);//PlayingNotice必要
	objectManager.HandleFontSet("G20", OBJECT_FONT_GOTHIC, 20);//一覧したの文字 

	//******************************************************************

	SceneManager sceneManager(objectManager, NOW_ACTIVE_JSON, jsonManager); // jsonで選択中のものを取得するものを放り込んでおく かつ，SceneManagerの定義

	sceneManager.ChanegeScene(SCENE::TAB_HOME);//初回起動はホーム

	HEADER_Scene headerScene(objectManager, musicManager, NOW_ACTIVE_JSON, jsonManager);

	SetWindowSize(App::DEFAULT_WINDOW_SIZE_X * 4 / 5, App::DEFAULT_WINDOW_SIZE_Y * 4 / 5); // 初期のウインドウサイズ 1920 * 1080 を想定

	SetWindowInitPosition(0, 0); // ウインドウの場所を設定動作確認では機能していない

	SetDrawMode(DX_DRAWMODE_ANISOTROPIC);

	while (!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen()) // メインループ この中の条件はないとバグるもの
	{

		// ↓処理関係

		Input::Mouse::Update();
		Input::KeyBoard::Update();

		objectManager.Update();
		sceneManager.Update();
		headerScene.Update();

		SetDrawScreen(DX_SCREEN_BACK); // 裏画面描画設定

		// ↓描画関係

		sceneManager.Draw();
		headerScene.Draw();
		objectManager.Draw();

		if (Ope::SCENE_CHANGE_FLAG) // これがTRUEの時シーンが切り替わる
		{
			sceneManager.ChanegeScene(Ope::SCENE_CHANGE_NUM);
		}

		//if (Input::KeyBoard::KEY[KEY_INPUT_ESCAPE] == KEYBOARD_PRESS_FIRST) { // Escを押すことで終了する機能 誤爆が多いらしいのでコメントアウト
			//break;
		//}
	}

	DxLib_End(); // Dxlib終了
	return 0;
}