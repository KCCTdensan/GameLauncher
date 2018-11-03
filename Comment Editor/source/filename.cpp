#include "filename.hpp"
#include "wmsg.hpp"


bool file_name::Open(HWND hWnd)
{
	TCHAR FilePath[MAX_PATH] = { 0 };
	TCHAR FileTitle[MAX_PATH] = { 0 };
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = TEXT(
		"�����`���[�p��i�����t�@�C��(*.apc)\0*.apc\0"
		"���ׂẴt�@�C��(*.*)\0*.*\0\0");
	ofn.lpstrFile = FilePath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = FileTitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrTitle = TEXT("�����`���[�p��i�����t�@�C�����J��");
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = TEXT("apc");

	if (GetOpenFileName(&ofn) == 0)
	{
		return false;
	}

	SendMessage(hWnd, WM_LOADDOCUMENT, (WPARAM)FilePath, MAX_PATH);

	return true;
}

bool file_name::SaveAs(HWND hWnd)
{
	TCHAR FilePath[MAX_PATH] = { 0 };
	TCHAR FileTitle[MAX_PATH] = { 0 };
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = TEXT(
		"�����`���[�p��i�����t�@�C��(*.apc)\0*.apc\0"
		"���ׂẴt�@�C��(*.*)\0*.*\0\0");
	ofn.lpstrFile = FilePath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = FileTitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrTitle = TEXT("�����`���[�p��i�����t�@�C�����J��");
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = TEXT("apc");

	if (GetSaveFileName(&ofn) == 0)
	{
		return false;
	}

	SendMessage(hWnd, WM_SAVEASDOCUMENT, (WPARAM)FilePath, MAX_PATH);

	return true;
}