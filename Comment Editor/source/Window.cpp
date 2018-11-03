#include "Window.hpp"


void window::Startup(LPTSTR lpCmdLine)
{
	PROCESS_INFORMATION pi = {};
	STARTUPINFO si = {};
	CreateProcess(NULL, lpCmdLine, NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
}

void window::SetWndTextFileName(HWND hWnd, LPCTSTR FileName)
{
	TCHAR WndText[MAX_PATH];
	wsprintf(WndText, TEXT("%s - Launcher Comment Editor"), FileName);
	SetWindowText(hWnd, WndText);
}