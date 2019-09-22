#include "file.hpp"
#include "document.hpp"
#include "wmsg.hpp"


namespace file
{
	Document Document;
}

bool file::LoadDocument(HWND hWnd, LPTSTR FilePath)
{
	bool Ret;

	TCHAR FileTitle[MAX_PATH];
	GetFileTitle(FilePath, FileTitle, MAX_PATH);

	Ret = Document.LoadFile(FilePath);
	Document.SetFilePath(FilePath);
	SendMessage(hWnd, WM_SETWNDTEXTFILENAME, (WPARAM)FileTitle, 0);

	return Ret;
}

bool file::SaveDocument()
{
	return Document.SaveFile();
}

bool file::SaveAsDocument(HWND hWnd, LPTSTR FilePath)
{
	bool Ret;

	TCHAR FileTitle[MAX_PATH];
	GetFileTitle(FilePath, FileTitle, MAX_PATH);

	Ret = Document.SaveAsFile(FilePath);
	Document.SetFilePath(FilePath);
	SendMessage(hWnd, WM_SETWNDTEXTFILENAME, (WPARAM)FileTitle, 0);

	return Ret;
}

Contents file::GetContents()
{
	return Document.GetContents();
}

void file::SetContents(const Contents&Contents)
{
	Document.SetContents(Contents);
}