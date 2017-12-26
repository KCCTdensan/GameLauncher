#include "wndproc.hpp"
#include "menu.hpp"
#include "wmsg.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
		MENU::CreateWndMenu(hWnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_COMMAND:
		MENU::onWM_COMMAND(hWnd, wp);
		return 0;

	case WM_EXIT:
		DestroyWindow(hWnd);
		return 0;

	case WM_FILEOPEN:
	case WM_FILESAVE:
	case WM_FILESAVEAS:
		return 0;

	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}