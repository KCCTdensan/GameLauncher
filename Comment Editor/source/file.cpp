#include "file.hpp"
#include "document.hpp"
#include "wmsg.hpp"


namespace FILE
{
	DOCUMENT Document;
}

bool FILE::LoadDocument(HWND hWnd, LPTSTR FilePath)
{
	bool Ret;

	TCHAR FileTitle[MAX_PATH];
	GetFileTitle(FilePath, FileTitle, MAX_PATH);

	Ret = Document.LoadFile(FilePath);
	Document.SetFilePath(FilePath);
	SendMessage(hWnd, WM_SETWNDTEXTFILENAME, (WPARAM)FileTitle, 0);

	return Ret;
}

bool FILE::SaveDocument()
{
	return Document.SaveFile();
}

bool FILE::SaveAsDocument(HWND hWnd, LPTSTR FilePath)
{
	bool Ret;

	TCHAR FileTitle[MAX_PATH];
	GetFileTitle(FilePath, FileTitle, MAX_PATH);

	Ret = Document.SaveAsFile(FilePath);
	Document.SetFilePath(FilePath);
	SendMessage(hWnd, WM_SETWNDTEXTFILENAME, (WPARAM)FileTitle, 0);

	return Ret;
}

CONTENTS FILE::GetContents()
{
	return Document.GetContents();
}

void FILE::SetContents(const CONTENTS&Contents)
{
	Document.SetContents(Contents);
}