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

void InputUpdate(); // threadA
void ApplicationUpdate(SceneManager* _sceneManager); // threadB

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) // windowsに定義された関数 ※修正不可
{
	const HWND MAIN_WINDOW_HANDLE = GetMainWindowHandle(); // ウインドウハンドル取得 ※修正不可

	SetAlwaysRunFlag(TRUE); // 画面がActiveでないときにも実行するか。音楽再生のため基本はTRUE
	ChangeWindowMode(TRUE); // 画面をウインドウにするか。TRUE:ウインドウ FALSE:全画面（ただし，全画面は描画が遅い。別の描画の仕方でされてしまうため。)
	SetWindowSizeChangeEnableFlag(TRUE);// ウインドウを可変にするかTRUEで可変
	SetUseDirectInputFlag(TRUE); // インプットのオブジェクトでダイレクトインプットを使用するかどうか。基本はTRUEの方が望ましい。

	ExePath exePath; //現在のカレントディレクトリを取得設定するためのクラスの変数宣言 ※修正不可

	SetWindowText("GameLauncher"); // アプリのタイトル名の変更

	if (DxLib_Init() == -1) // Dxlib初期化 ！この後じゃないと，画像・フォントハンドル操作や描画操作が動かない
	{
		return -1; // 初期化失敗の場合は終了 ※基本は問題ない
	}

	MSG msg;

#if _DEBUG // DEBUGの時の宣言 現時点で特に記述はなし
	// .vcxprojのディレクトリに放り込む
#else
	SetCurrentDirectory(exePath.GetPath());//こちらにも完成時にCopy&Paste
#endif

	SetMouseDispFlag(TRUE); // マウスを表示するか。全画面ではデフォでは表示されないため

	SetWindowStyleMode(1); // ボーダレスウインドウ

	SetWindowInitPosition(0, 0); // ウインドウの場所を設定動作確認では機能していない

	SetDrawMode(DX_DRAWMODE_ANISOTROPIC);

	SetDrawArea(0, 0, (int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y);

	SetGraphMode((int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y, 32);

	SceneManager sceneManager;

	//std::thread inputUpdate(InputUpdate);
	//std::thread applicationUpdate(ApplicationUpdate, &sceneManager);

	//while (!ProcessMessage() && !ScreenFlip()) {
	//	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
	//		MainThread::SetEnd(true);
	//		break;
	//	}
	//	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	//}
	while (!ScreenFlip() && !ClearDrawScreen() && !MainThread::SetEnd()) // メインループ この中の条件はないとバグるもの
	{
		GetMessage(&msg, NULL, 0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		SetDrawScreen(DX_SCREEN_BACK);
		Input::MouseInput::Update();
		sceneManager.Update(); // ループ内で継続して使用，ヘッダーはそれぞれでインスタンス化してください
		sceneManager.Draw();

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

void InputUpdate() {
	while (!MainThread::SetEnd()) {

		Input::MouseInput::Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void ApplicationUpdate(SceneManager* _sceneManager) {
	while (!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen() && !MainThread::SetEnd()) // メインループ この中の条件はないとバグるもの
	{
		_sceneManager->Update(); // ループ内で継続して使用，ヘッダーはそれぞれでインスタンス化してください
		_sceneManager->Draw();

		/*std::string tmp = std::to_string(Input::MouseInput::GetMouse().x);
		std::string tmp2 = std::to_string(Input::MouseInput::GetMouse().y);
		DrawString(500, 500, tmp.c_str(), GetColor(255, 255, 255));*/
	}
}