#pragma once
#include "AppClose.h"
#include "DxLib.h"
#include <windows.h>
class WindowHwnd
{
public:
	static void WindowMaximize(HWND hwnd);
	static void WindowMinimize(HWND hwnd);
	static void WindowClose(HWND hwnd);
	static void WindowNormalize(HWND hwnd);
};

