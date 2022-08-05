#include "WindowHwnd.h"

void WindowHwnd::WindowMaximize(HWND hwnd)
{
	SetWindowStyleMode(4);
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
	SetWindowStyleMode(11);
}
