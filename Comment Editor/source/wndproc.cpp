#include "wndproc.hpp"
#include "file.hpp"
#include "filename.hpp"
#include "menu.hpp"
#include "wnd.hpp"
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

	case WM_LOADFILE:
		FILE::Load(((FILENAMESTRUCT*)wp)->FilePath, (int)lp);
		SendMessage(hWnd, WM_SETWNDTEXTFILENAME, (WPARAM)(((FILENAMESTRUCT*)wp)->FileTitle), 0);
		return 0;

	case WM_SAVEFILE:
		FILE::Save(((FILENAMESTRUCT*)wp)->FilePath, (int)lp);
		SendMessage(hWnd, WM_SETWNDTEXTFILENAME, (WPARAM)(((FILENAMESTRUCT*)wp)->FileTitle), 0);
		return 0;

	case WM_SETWNDTEXTFILENAME:
		WND::SetWndTextFileName(hWnd, (LPCTSTR)wp);
		return 0;

	case WM_FILE_OPEN:
		FILENAME::Open(hWnd);
		return 0;

	case WM_FILE_SAVE:
		FILENAME::Save(hWnd);
		return 0;

	case WM_FILE_SAVEAS:
		FILENAME::SaveAs(hWnd);
		return 0;

	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}