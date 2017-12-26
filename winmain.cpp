#include <Windows.h>
#include "wndproc.h"


const static TCHAR WND_CLS_NAME[] = TEXT("GAMELAUNCHER");


ATOM RegWndCls(HINSTANCE hInstance)
{
	WNDCLASS wndcls;

	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	wndcls.lpfnWndProc = WndProc;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hInstance = hInstance;
	wndcls.hIcon = NULL;
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndcls.lpszMenuName = NULL;
	wndcls.lpszClassName = WND_CLS_NAME;

	return RegisterClass(&wndcls);
}

bool CreateMainWnd()
{
	RECT WindowRect;

	GetWindowRect(GetDesktopWindow(), &WindowRect);

	HWND hWnd = CreateWindow(WND_CLS_NAME, TEXT("Game Launcher"), WS_POPUP,
		0, 0, WindowRect.right, WindowRect.bottom,
		NULL, NULL, NULL, NULL);

	if (hWnd == NULL)
	{
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);

	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	bool loop = true;
	MSG msg;

	if (RegWndCls(hInstance) == 0)
	{
		return -1;
	}

	if (!CreateMainWnd())
	{
		return -1;
	}


	while (loop)
	{
		BOOL ret = GetMessage(&msg, NULL, 0, 0);

		switch (ret)
		{
		case -1:
		case 0:
			loop = false;
			break;

		default:
			DispatchMessage(&msg);
			break;
		}
	}

	return (int)msg.wParam;
}