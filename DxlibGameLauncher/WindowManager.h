#pragma once

#include <Windows.h>


class WindowManager
{
public:
	void Update(HWND mainWindowHandle);

private:
	int XWindowMode;
	int YWindowMode;
};