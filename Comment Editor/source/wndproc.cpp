#include "wndproc.hpp"
#include "wmsg.hpp"
#include "document.hpp"
#include "edit.hpp"
#include "file.hpp"
#include "filename.hpp"
#include "menu.hpp"
#include "Window.hpp"


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
		menu::CreateWndMenu(hWnd);
		edit::Prepare(hWnd);
		ShowWindow(hWnd, SW_SHOW);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		edit::Paint(hWnd);
		return 0;

	case WM_COMMAND:
		menu::Command(hWnd, LOWORD(wp));
		edit::Command(hWnd, HIWORD(wp), LOWORD(wp));
		return 0;

	case WM_CREATEDOCUMENT:
		window::Startup(GetCommandLine());
		return 0;

	case WM_LOADDOCUMENT:
		file::LoadDocument(hWnd, (LPTSTR)wp);
		edit::SetContents(file::GetContents());
		edit::UpdateCommentNumOfWritten(hWnd);
		return 0;

	case WM_SAVEDOCUMENT:
		file::SetContents(edit::GetContents());
		return file::SaveDocument() ? 0 : -1;

	case WM_SAVEASDOCUMENT:
		file::SetContents(edit::GetContents());
		return file::SaveAsDocument(hWnd, (LPTSTR)wp) ? 0 : -1;

	case WM_SETWNDTEXTFILENAME:
		window::SetWndTextFileName(hWnd, (LPCTSTR)wp);
		return 0;

	case WM_FILENAME_OPEN:
		file_name::Open(hWnd);
		return 0;

	case WM_FILENAME_SAVEAS:
		file_name::SaveAs(hWnd);
		return 0;

	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}