#include "WindowHwnd.h"

void WindowHwnd::WindowMaximize(HWND hwnd)
{
	//SetWindowLongPtr(GetMainWindowHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
	ShowWindow(hwnd, SW_MAXIMIZE);
}

void WindowHwnd::WindowMinimize(HWND hwnd)
{
	WindowNormalize(hwnd);
	ShowWindow(hwnd, SW_MINIMIZE);
}

void WindowHwnd::WindowClose(HWND hwnd)
{
	AppClose::Close();
}

void WindowHwnd::WindowNormalize(HWND hwnd)
{
	ShowWindow(hwnd, SW_SHOWNORMAL);
	SetWindowLongPtr(GetMainWindowHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
	SetWindowPos(GetMainWindowHandle(), NULL, 0, 0, 0, 0, (SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED));
}
