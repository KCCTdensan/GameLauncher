#include <Windows.h>
#include "wndproc.hpp"


const static TCHAR CLSNAME[] = TEXT("MAIN WND");
const static TCHAR WNDNAME[] = TEXT("Comment Editor");

ATOM RegWndCls(HINSTANCE hInstance)
{
	WNDCLASS wndcls;

	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	wndcls.lpfnWndProc = WndProc;
	wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
	wndcls.hInstance = hInstance;
	wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndcls.lpszMenuName = NULL;
	wndcls.lpszClassName = CLSNAME;

	return RegisterClass(&wndcls);
}

bool CreateMainWnd()
{
	HWND hWnd = CreateWindow(
		CLSNAME, WNDNAME, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
		NULL, NULL, NULL, NULL
	);

	return hWnd != NULL;
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
			TranslateMessage(&msg);
			break;
		}
	}

	return (int)msg.wParam;
}