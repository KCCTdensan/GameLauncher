#include "wndproc.hpp"
#include "wmsg.hpp"
#include "document.hpp"
#include "edit.hpp"
#include "file.hpp"
#include "filename.hpp"
#include "menu.hpp"
#include "wnd.hpp"


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
		MENU::CreateWndMenu(hWnd);
		EDIT::Prepare(hWnd);
		ShowWindow(hWnd, SW_SHOW);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		EDIT::Paint(hWnd);
		return 0;

	case WM_COMMAND:
		MENU::Command(hWnd, LOWORD(wp));
		EDIT::Command(HIWORD(wp), LOWORD(wp));
		return 0;

	case WM_CREATEDOCUMENT:
		WND::Startup(GetCommandLine());
		return 0;

	case WM_LOADDOCUMENT:
		FILE::LoadDocument(hWnd, (LPTSTR)wp);
		EDIT::SetContents(FILE::GetContents());
		return 0;

	case WM_SAVEDOCUMENT:
		FILE::SetContents(EDIT::GetContents());
		return FILE::SaveDocument() ? 0 : -1;

	case WM_SAVEASDOCUMENT:
		FILE::SetContents(EDIT::GetContents());
		return FILE::SaveAsDocument(hWnd, (LPTSTR)wp) ? 0 : -1;

	case WM_SETWNDTEXTFILENAME:
		WND::SetWndTextFileName(hWnd, (LPCTSTR)wp);
		return 0;

	case WM_FILENAME_OPEN:
		FILENAME::Open(hWnd);
		return 0;

	case WM_FILENAME_SAVEAS:
		FILENAME::SaveAs(hWnd);
		return 0;

	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}