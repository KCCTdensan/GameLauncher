#include "DxLib.h"
#include <Windows.h>
#include <WinUser.h>
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
#include "WelcomeScene.h"
#include "ApplicationTime.h"
#include "AppClose.h"
#include "MouseInput.h"
#include "KeyboardInput.h"
#include "MusicPlayer.h"
#include "OwnerPlayingScene.h"

/*void InputUpdate(); // threadA
void ApplicationUpdate(SceneManager* _sceneManager); // threadB*/

#define WM_NOTIFYICON (WM_USER + 100)

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	/*case WM_LBUTTONDOWN:
		if (Input::MouseInput::GetMouse().y <= 5.f) {
			SendMessage(hwnd, WM_NCLBUTTONDOWN, HTSIZE, 0);
		}
		return 0;*/
	case WM_NCHITTEST:
		RECT rec;
		GetWindowRect(hwnd, &rec);
		int mousex = LOWORD(lp);
		int mousey = HIWORD(lp);
		if (mousex < rec.left)
			return HTNOWHERE;
		if (mousex >= rec.right)
			return HTNOWHERE;
		if (mousey < rec.top)
			return HTNOWHERE;
		if (mousey >= rec.bottom)
			return HTNOWHERE;

		int xblock = (mousex - rec.left) * 16 / (rec.right - rec.left);
		int yblock = (mousey - rec.top) * 9 / (rec.bottom - rec.top);
		if (xblock == 0 && yblock == 0) 
			return HTTOPLEFT;
		if (xblock == 0 && yblock == 15)
			return HTBOTTOMLEFT;
		if (xblock == 15 && yblock == 0)
			return HTTOPRIGHT;
		if (xblock == 15 && yblock == 8) 
			return HTBOTTOMRIGHT;
		if (xblock == 0)
			return HTLEFT;
		if (xblock == 15)
			return HTRIGHT;
		if (yblock == 0)
			return HTTOP;
		if (yblock == 8)
			return HTBOTTOM;
		return HTCLIENT;
	}
	return 0;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) // windowsに定義された関数 ※修正不可
{
	ExePath exePath; //現在のカレントディレクトリを取得設定するためのクラスの変数宣言 ※修正不可
	SetOutApplicationLogValidFlag(FALSE);

	SetCurrentDirectory(exePath.GetPath());//こちらにも完成時にCopy&Paste

	const HWND MAIN_WINDOW_HANDLE = GetMainWindowHandle(); // ウインドウハンドル取得 ※修正不可

	//SetMultiThreadFlag(TRUE); // マルチスレッド対応
	SetAlwaysRunFlag(TRUE); // 画面がActiveでないときにも実行するか。音楽再生のため基本はTRUE
	ChangeWindowMode(TRUE); // 画面をウインドウにするか。TRUE:ウインドウ FALSE:全画面（ただし，全画面は描画が遅い。別の描画の仕方でされてしまうため。)
	SetWindowSizeChangeEnableFlag(TRUE);// ウインドウを可変にするかTRUEで可変
	SetUseDirectInputFlag(TRUE); // インプットのオブジェクトでダイレクトインプットを使用するかどうか。基本はTRUEの方が望ましい。
	SetMainWindowText("Launcher"); // アプリのタイトル名の変更
	SetUseIMEFlag(TRUE);
	SetUseTSFFlag(FALSE);

	SetGraphMode((int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y, 32);

	Color255 bgColor("#dafcf5");
	SetBackgroundColor(bgColor.r, bgColor.g, bgColor.b);

	//SetUseDirectInputFlag(FALSE);

	if (DxLib_Init() == -1) // Dxlib初期化 ！この後じゃないと，画像・フォントハンドル操作や描画操作が動かない
	{
		return -1; // 初期化失敗の場合は終了 ※基本は問題ない
	}

	ApplicationBuilder applicationBuilder;

	//MSG msg;
	SetHookWinProc(WndProc);

	PosVec monitorSize((float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN));

	SetMouseDispFlag(TRUE); // マウスを表示するか。全画面ではデフォでは表示されないため

	//SetWindowInitPosition(0, 0); // ウインドウの場所を設定動作確認では機能していない

	SetDrawMode(DX_DRAWMODE_ANISOTROPIC);

	SetDrawArea(0, 0, (int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y);

	SetWindowSize((int)(monitorSize.x) * 4 / 5, (int)monitorSize.y * 4 / 5);
	SetWindowMinSize((int)(monitorSize.x) / 4, (int)(monitorSize.y) / 4);

	SceneManager::Initialize();

	SceneManager::ChangeScene("ゲームランチャーならこれができる!", new OwnerPlayingScene(SceneManager::GetSharingScenes()), false);
	//SceneManager::ChangeScene("Welcome", new WelcomeScene(SceneManager::GetSharingScenes()), false, false); // 最初に表示するページ

	//std::thread inputUpdate(InputUpdate);
	//std::thread applicationUpdate(ApplicationUpdate, &sceneManager);

	SetWindowLongPtr(GetMainWindowHandle(), GWL_EXSTYLE, WS_EX_TRANSPARENT);
	WindowHwnd::WindowNormalize(GetMainWindowHandle());


	while (!ScreenFlip() && !ClearDrawScreen() && !MainThread::SetEnd()) // メインループ この中の条件はないとバグるもの
	{	
		applicationBuilder.Update(); // システム系更新処理(がまとめられている)
		ProcessMessage();

		SetDrawScreen(DX_SCREEN_BACK); // 描画初期化
		Input::MouseInput::Update(); // マウス更新処理
		Input::KeyboardInput::Update(); // キーボード更新処理
		MusicPlayer::Update();

		if (GetWindowActiveFlag()) SceneManager::Collide();
		SceneManager::Update();
		SceneManager::Draw(); // シーン更新処理

		SceneManager::UpdateForwardBackwardScene(
			Input::MouseInput::GetClick(MOUSE_INPUT_5), PressFrame::FIRST,
			Input::MouseInput::GetClick(MOUSE_INPUT_4), PressFrame::FIRST);

		if (AppClose::GetClosed()) {
			MainThread::SetEnd(true);
			break;
		}
	}

	DxLib_End(); // ライブラリend
	return 0;
}