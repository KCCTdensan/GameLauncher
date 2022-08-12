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
#include "DebugScene.h"
#include "ApplicationTime.h"
#include "AppClose.h"
#include "MouseInput.h"

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

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) // windowsに定義された関数 ※修正不可
{
	ExePath exePath; //現在のカレントディレクトリを取得設定するためのクラスの変数宣言 ※修正不可
	SetOutApplicationLogValidFlag(FALSE);

#if _DEBUG // DEBUGの時の宣言 現時点で特に記述はなし
	// .vcxprojのディレクトリに放り込む
#else
	SetCurrentDirectory(exePath.GetPath());//こちらにも完成時にCopy&Paste
#endif

	const HWND MAIN_WINDOW_HANDLE = GetMainWindowHandle(); // ウインドウハンドル取得 ※修正不可

	//SetMultiThreadFlag(TRUE); // マルチスレッド対応
	SetAlwaysRunFlag(TRUE); // 画面がActiveでないときにも実行するか。音楽再生のため基本はTRUE
	ChangeWindowMode(TRUE); // 画面をウインドウにするか。TRUE:ウインドウ FALSE:全画面（ただし，全画面は描画が遅い。別の描画の仕方でされてしまうため。)
	SetWindowSizeChangeEnableFlag(TRUE);// ウインドウを可変にするかTRUEで可変
	SetUseDirectInputFlag(TRUE); // インプットのオブジェクトでダイレクトインプットを使用するかどうか。基本はTRUEの方が望ましい。
	SetMainWindowText("Launcher"); // アプリのタイトル名の変更
	SetUseIMEFlag(TRUE);
	SetUseTSFFlag(FALSE);

	//SetWindowStyleMode(11); // ボーダレスウインドウ

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

	SceneManager::ChangeScene("debug", new DebugScene(), false); // 最初に表示するページ

	//std::thread inputUpdate(InputUpdate);
	//std::thread applicationUpdate(ApplicationUpdate, &sceneManager);

	SetWindowLongPtr(GetMainWindowHandle(), GWL_EXSTYLE, WS_EX_TRANSPARENT);
	WindowHwnd::WindowNormalize(GetMainWindowHandle());


	while (!ScreenFlip() && !ClearDrawScreen() && !MainThread::SetEnd()) // メインループ この中の条件はないとバグるもの
	{	
		applicationBuilder.Update(); // システム系更新処理(がまとめられている)
		//GetMessage(&msg, NULL, 0, 0); // 3,4 最小値最大値
		//TranslateMessage(&msg);
		//DispatchMessage(&msg); // ウインドウメッセージ処理
		ProcessMessage();

		SetDrawScreen(DX_SCREEN_BACK); // 描画初期化
		Input::MouseInput::Update(); // マウス更新処理

		SceneManager::Collide();
		SceneManager::Update();
		SceneManager::Draw(); // シーン更新処理

		//GradX_RGB(10, 200, 630, 280, 255, 128, 0, 0, 255, 128);

		SceneManager::UpdateForwardBackwardScene(
			Input::MouseInput::GetClick(MOUSE_INPUT_5), PressFrame::FIRST,
			Input::MouseInput::GetClick(MOUSE_INPUT_4), PressFrame::FIRST);

		if (AppClose::GetClosed()) {
			MainThread::SetEnd(true);
			break;
		}
	}

	//inputUpdate.join();
	//applicationUpdate.join();

	DxLib_End(); // ライブラリend
	return 0;
}

/*void InputUpdate() {
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

		std::string tmp = std::to_string(Input::MouseInput::GetMouse().x);
		std::string tmp2 = std::to_string(Input::MouseInput::GetMouse().y);
		DrawString(500, 500, tmp.c_str(), GetColor(255, 255, 255));
	}
}*/