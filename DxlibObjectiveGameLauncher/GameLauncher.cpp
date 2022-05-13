#include "DxLib.h"
#include <Windows.h>
#include "ExePath.h"
#include "ApplicationPreference.h"
#include "SceneManager.h"

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

	SceneManager sceneManager;

	while (!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen()) // メインループ この中の条件はないとバグるもの
	{
		sceneManager.Update();
		sceneManager.Draw();
		if (CheckHitKeyAll()) break;
	}

	DxLib_End();
	return 0;
}