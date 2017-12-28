#include "wndproc.hpp"
#include "document.hpp"
#include "filename.hpp"
#include "menu.hpp"
#include "wnd.hpp"
#include "wmsg.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
#ifdef MDI
	static HWND hClientWnd;
#endif

	switch (msg)
	{
	case WM_CREATE:
		MENU::CreateWndMenu(hWnd);
#ifdef MDI
		hClientWnd = WND::CreateClientWnd(hWnd);
#endif
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_COMMAND:
		MENU::onWM_COMMAND(hWnd, wp);
		return 0;

	case WM_CREATEDOCUMENT:
#ifdef MDI
		DOCUMENT::CreateDocument(hClientWnd);
#else
		WND::Startup(GetCommandLine());
#endif
		return 0;

	case WM_LOADDOCUMENT:
		DOCUMENT::LoadFile(((FILENAMESTRUCT*)wp)->FilePath, (int)lp);
		SendMessage(hWnd, WM_SETWNDTEXTFILENAME, (WPARAM)((FILENAMESTRUCT*)wp)->FileTitle, 0);
		return 0;

	case WM_SAVEDOCUMENT:
		DOCUMENT::SaveFile(((FILENAMESTRUCT*)wp)->FilePath, (int)lp);
		SendMessage(hWnd, WM_SETWNDTEXTFILENAME, (WPARAM)((FILENAMESTRUCT*)wp)->FileTitle, 0);
		return 0;

	case WM_SETWNDTEXTFILENAME:
#ifndef MDI
		WND::SetWndTextFileName(hWnd, (LPCTSTR)wp);
#endif
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
#ifdef MDI
		return DefFrameProc(hWnd, hClientWnd, msg, wp, lp);
#else
		return DefWindowProc(hWnd, msg, wp, lp);
#endif
	}
}