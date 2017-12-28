#pragma once

#include <Windows.h>

#ifndef INCLUDE_WND_HPP
#define INCLUDE_WND_HPP


namespace WND
{
	ATOM RegWndCls(HINSTANCE hInstance);
	bool CreateMainWnd();

#ifdef MDI
	ATOM RegMDIChildCls(HINSTANCE hInstance);
	HWND CreateClientWnd(HWND hWnd);
	HWND CreateMDIWnd(HWND hClientWnd);
#else
	void Startup(LPTSTR lpCmdLine);
	void SetWndTextFileName(HWND hWnd, LPCTSTR FileName);
#endif

}


#endif