#include "StartUp.hpp"
#include <process.h>
#include <wmsg.h>


unsigned int __stdcall StartUp::Thread(void*Arg)
{
	Sleep(3000);
	return 0;
}

StartUp::StartUp(HWND hWnd, SceneChangerInterface*SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight) :Scene(SceneChanger, BmpWidth, BmpHeight)
{
	hBrushBkgnd = CreateSolidBrush(BkgndColor);
	hPenBkgnd = CreatePen(PS_SOLID, 0, BkgndColor);
}

StartUp::~StartUp()
{	
	HDC hdc = GethMemDC();
	SelectObject(hdc, GetStockObject(NULL_BRUSH));//hMemDCがまだ破棄されていないので、別のブラシを選択しておく
	SelectObject(hdc, GetStockObject(NULL_PEN));//hMemDCがまだ破棄されていないので、別のペンを選択しておく
	DeleteObject(hBrushBkgnd);
	DeleteObject(hPenBkgnd);
	hBrushBkgnd = NULL;
	hPenBkgnd = NULL;
}

int StartUp::Initialize(HWND hWnd)
{
	HDC hdc = GethMemDC();

	//背景を塗りつぶす
	SelectObject(hdc, hBrushBkgnd);
	SelectObject(hdc, hPenBkgnd);
	Rectangle(hdc, 0, 0, GetWidth(), GetHeight());
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);

	hThread = (HANDLE)_beginthreadex(NULL, 0, Thread, NULL, 0, &ThreadID);
	if (hThread == NULL)
	{
		return -1;
	}
	PostMessage(hWnd, WM_GUI_UPDATE, 0, 0);

	return 0;
}

int StartUp::Finalize(HWND hWnd)
{
	CloseHandle(hThread);
	hThread = NULL;
	return 0;
}

int StartUp::Update(HWND hWnd)
{
	//描画処理
	static int right = 21;
	HDC hdc = GethMemDC();
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	Rectangle(hdc, 20, 400, right, 500);
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	right++;

	//別スレッドが稼働中かどうか確認
	DWORD ExitCode;
	GetExitCodeThread(hThread, &ExitCode);
	if (ExitCode == STILL_ACTIVE)//稼働している場合はアニメーションを続ける
	{
		PostMessage(hWnd, WM_GUI_UPDATE, 0, 0);
	}
	else//終了している場合はシーンを切り替える
	{
		SceneChanger->ChangeScene(hWnd, SceneName_MainMenu);//シーン切り替え
	}
	return 0;
}