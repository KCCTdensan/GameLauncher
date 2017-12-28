#include "filename.hpp"
#include "wmsg.h"


void FILENAME::Open(HWND hWnd)
{
	FILENAMESTRUCT fns = { 0 };
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = TEXT(
		"ランチャーコメントファイル(*.apc)\0*.apc\0"
		"すべてのファイル(*.*)\0*.*\0\0");
	ofn.lpstrFile = fns.FilePath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = fns.FileTitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrTitle = TEXT("ランチャーコメントファイルを開く");
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = TEXT("apc");

	if (GetOpenFileName(&ofn) == 0)
	{
		return;
	}

	fns.MaxPath = fns.MaxTitle = MAX_PATH;

	SendMessage(hWnd, WM_LOADDOCUMENT, (WPARAM)&fns, MAX_PATH);
}

void FILENAME::Save(HWND hWnd)
{

}

void FILENAME::SaveAs(HWND hWnd)
{
	FILENAMESTRUCT fns = { 0 };
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = TEXT(
		"ランチャーコメントファイル(*.apc)\0*.apc\0"
		"すべてのファイル(*.*)\0*.*\0\0");
	ofn.lpstrFile = fns.FilePath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = fns.FileTitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrTitle = TEXT("ランチャーコメントファイルを開く");
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = TEXT("apc");

	if (GetSaveFileName(&ofn) == 0)
	{
		return;
	}

	fns.MaxPath = fns.MaxTitle = MAX_PATH;

	SendMessage(hWnd, WM_SAVEDOCUMENT, (WPARAM)&fns, MAX_PATH);
}