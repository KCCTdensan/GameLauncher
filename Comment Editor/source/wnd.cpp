#include "wnd.hpp"


void WND::Startup(LPTSTR lpCmdLine)
{
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	CreateProcess(NULL, lpCmdLine, NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
}

void WND::SetWndTextFileName(HWND hWnd, LPCTSTR FileName)
{
	TCHAR WndText[MAX_PATH];
	wsprintf(WndText, TEXT("%s - Launcher Comment Editor"), FileName);
	SetWindowText(hWnd, WndText);
}