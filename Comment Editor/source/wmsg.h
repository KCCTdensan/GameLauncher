#pragma once

#include <Windows.h>

#define WM_CREATEDOCUMENT		0x0400
#define WM_LOADDOCUMENT			0x0401
#define WM_SAVEDOCUMENT			0x0402
struct FILENAMESTRUCT
{
	TCHAR FilePath[MAX_PATH];
	int MaxPath;
	TCHAR FileTitle[MAX_PATH];
	int MaxTitle;
};

#define WM_SETWNDTEXTFILENAME	0x0500
#define WM_FILE_OPEN			0x0510
#define WM_FILE_SAVE			0x0511
#define WM_FILE_SAVEAS			0x0512
#define WM_HELP_HOWTOUSE		0x0520
#define WM_HELP_VERSION			0x0521