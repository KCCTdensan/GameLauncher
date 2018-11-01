#include <Windows.h>
#include "wndproc.hpp"


const static TCHAR CLS_NAME[] = TEXT("MAINWND");
const static TCHAR WND_NAME[] = TEXT("Comment Editor for KCCT Launcher");

ATOM RegWndCls(HINSTANCE hInst)
{
	WNDCLASS wndcls;

	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	wndcls.lpfnWndProc = WndProc;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hInstance = hInst;
	wndcls.hIcon = NULL;
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndcls.lpszMenuName = NULL;
	wndcls.lpszClassName = CLS_NAME;

	return RegisterClass(&wndcls);
}

bool CreateMainWnd()
{
	return CreateWindow(CLS_NAME, WND_NAME, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 700,
		NULL, NULL, NULL, NULL) != NULL;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	bool Loop = true;
	MSG Msg;

	if (RegWndCls(hInst) == 0)
	{
		return -1;
	}
	if (!CreateMainWnd())
	{
		return -1;
	}

	while (Loop)
	{
		BOOL Ret = GetMessage(&Msg, NULL, 0, 0);

		switch (Ret)
		{
		case -1:
		case 0:
			Loop = false;
			break;

		default:
			DispatchMessage(&Msg);
			TranslateMessage(&Msg);
			break;
		}
	}

	return (int)Msg.wParam;
}