#include "wnd.hpp"


void WND::SetWndTextFileName(HWND hWnd, LPCTSTR FileName)
{
	TCHAR WndText[MAX_PATH];
	wsprintf(WndText, TEXT("%s - Launcher Comment Editor"), FileName);
	SetWindowText(hWnd, WndText);
}