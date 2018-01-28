#pragma once

#include <Windows.h>

#ifndef INCLUDE_WND_HPP
#define INCLUDE_WND_HPP


namespace WND
{
	void Startup(LPTSTR lpCmdLine);
	void SetWndTextFileName(HWND hWnd, LPCTSTR FileName);
}


#endif