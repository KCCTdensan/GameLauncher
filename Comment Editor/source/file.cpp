#include "file.hpp"
#include "document.hpp"
#include "wmsg.hpp"


namespace FILE
{
	DOCUMENT Document;
}

void FILE::LoadDocument(HWND hWnd, LPTSTR FilePath)
{
	TCHAR FileTitle[MAX_PATH];
	GetFileTitle(FilePath, FileTitle, MAX_PATH);

	Document.LoadFile(FilePath);
	Document.SetFilePath(FilePath);
	SendMessage(hWnd, WM_SETWNDTEXTFILENAME, (WPARAM)FileTitle, 0);
}

void FILE::SaveDocument()
{
	Document.SaveFile();
}

void FILE::SaveAsDocument(HWND hWnd, LPTSTR FilePath)
{
	TCHAR FileTitle[MAX_PATH];
	GetFileTitle(FilePath, FileTitle, MAX_PATH);

	Document.SaveAsFile(FilePath);
	Document.SetFilePath(FilePath);
	SendMessage(hWnd, WM_SETWNDTEXTFILENAME, (WPARAM)FileTitle, 0);
}

CONTENTS FILE::GetContents()
{
	return Document.GetContents();
}

void FILE::SetContents(const CONTENTS&Contents)
{
	Document.SetContents(Contents);
}