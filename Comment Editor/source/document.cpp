#include "document.hpp"
#include "wnd.hpp"
#include "contents.hpp"


void DOCUMENT::LoadFile(LPCTSTR FilePath, int MaxPath)
{
	CONTENTS Buf;

	HANDLE hFile = CreateFile(FilePath, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, &Buf, sizeof(CONTENTS), NULL, NULL);

	CloseHandle(hFile);
}

void DOCUMENT::SaveFile(LPCTSTR FilePath, int MaxPath)
{
	CONTENTS Buf;

	HANDLE hFile = CreateFile(FilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	WriteFile(hFile, &Buf, sizeof(CONTENTS), NULL, NULL);

	CloseHandle(hFile);
}

#ifdef MDI

void DOCUMENT::CreateDocument(HWND hClientWnd)
{
	WND::CreateMDIWnd(hClientWnd);
}

#endif