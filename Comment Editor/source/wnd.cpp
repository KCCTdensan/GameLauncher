#include "wnd.hpp"
#include "wndproc.hpp"
#include "menu.hpp"


namespace WND
{
	const static TCHAR WND_CLS_NAME[] = TEXT("GAMELAUNCHER");
#ifdef MDI
	const static TCHAR MDI_CHILD_CLS_NAME[] = TEXT("MDICHILD");
#endif
}


ATOM WND::RegWndCls(HINSTANCE hInstance)
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

bool WND::CreateMainWnd()
{
	HWND hWnd = CreateWindow(WND_CLS_NAME, TEXT("Launcher Comment Editor"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, NULL, NULL);

	if (hWnd == NULL)
	{
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);

	return true;
}

#ifdef MDI

ATOM WND::RegMDIChildCls(HINSTANCE hInstance)
{
	WNDCLASS wndcls;

	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	wndcls.lpfnWndProc = DefMDIChildProc;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hInstance = hInstance;
	wndcls.hIcon = NULL;
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndcls.lpszMenuName = NULL;
	wndcls.lpszClassName = MDI_CHILD_CLS_NAME;

	return RegisterClass(&wndcls);
}

HWND WND::CreateClientWnd(HWND hWnd)
{
	CLIENTCREATESTRUCT ccs;
	ccs.hWindowMenu = MENU::GetEditMenuHandle();
	ccs.idFirstChild = 0x0100;

	return CreateWindow(TEXT("MDICLIENT"), NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
		0, 0, 0, 0, hWnd, (HMENU)1, NULL, &ccs);
}

HWND WND::CreateMDIWnd(HWND hClientWnd)
{
	return CreateMDIWindow(MDI_CHILD_CLS_NAME, TEXT("–³‘è"), 0,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		hClientWnd, NULL, NULL);
}

#else

void WND::Startup(LPTSTR lpCmdLine)
{
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	CreateProcess(NULL, lpCmdLine, NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
}

void WND::SetWndTextFileName(HWND hWnd, LPCTSTR FileName)
{
	TCHAR WndText[MAX_PATH];
	wsprintf(WndText, TEXT("%s - Launcher Comment Editor"), FileName);
	SetWindowText(hWnd, WndText);
}

#endif