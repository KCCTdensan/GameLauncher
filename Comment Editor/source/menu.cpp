#include "menu.hpp"
#include "wmsg.h"


#define IDM_FILE				0x0000
#define IDM_FILE_OPEN			0x0001
#define IDM_FILE_SAVE			0x0002
#define IDM_FILE_SAVEAS			0x0003
#define IDM_FILE_EXIT			0x0004
#define IDM_HELP				0x0300
#define IDM_HELP_HOWTOUSE		0x0301
#define IDM_HELP_VERSION		0x0302


namespace MENU
{
	HMENU hMenu;
	HMENU hMenu_File;
	HMENU hMenu_Help;
}


void MENU::CreateWndMenu(HWND hWnd)
{
	TCHAR Str_File[] = TEXT("ファイル(&F)");
	TCHAR Str_File_Open[] = TEXT("開く(&O)");
	TCHAR Str_File_Save[] = TEXT("上書き保存(&S)");
	TCHAR Str_File_SaveAs[] = TEXT("名前を付けて保存(&A)");
	TCHAR Str_File_Exit[] = TEXT("終了(&X)");
	TCHAR Str_Help[] = TEXT("ヘルプ(&H)");
	TCHAR Str_Help_HowToUse[] = TEXT("GEOMETRYの使い方(&U)");
	TCHAR Str_Help_Version[] = TEXT("バージョン情報(&A)");

	MENUITEMINFO mii;

	hMenu = CreateMenu();
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fType = MFT_STRING;

	//ファイル(&F)
	hMenu_File = CreateMenu();
	mii.fMask = MIIM_TYPE | MIIM_SUBMENU | MIIM_ID;
	mii.wID = IDM_FILE;
	mii.hSubMenu = hMenu_File;
	mii.dwTypeData = Str_File;
	InsertMenuItem(hMenu, IDM_FILE, true, &mii);

	mii.fMask = MIIM_TYPE | MIIM_ID;
	mii.wID = IDM_FILE_OPEN;
	mii.dwTypeData = Str_File_Open;
	InsertMenuItem(hMenu_File, IDM_FILE_OPEN, true, &mii);
	mii.wID = IDM_FILE_SAVE;
	mii.dwTypeData = Str_File_Save;
	InsertMenuItem(hMenu_File, IDM_FILE_SAVE, true, &mii);
	mii.wID = IDM_FILE_SAVEAS;
	mii.dwTypeData = Str_File_SaveAs;
	InsertMenuItem(hMenu_File, IDM_FILE_SAVEAS, true, &mii);
	mii.wID = IDM_FILE_EXIT;
	mii.dwTypeData = Str_File_Exit;
	InsertMenuItem(hMenu_File, IDM_FILE_EXIT, true, &mii);

	//ヘルプ(&H)
	hMenu_Help = CreateMenu();
	mii.fMask = MIIM_TYPE | MIIM_SUBMENU | MIIM_ID;
	mii.wID = IDM_HELP;
	mii.hSubMenu = hMenu_Help;
	mii.dwTypeData = Str_Help;
	InsertMenuItem(hMenu, IDM_HELP, true, &mii);

	mii.fMask = MIIM_TYPE | MIIM_ID;
	mii.wID = IDM_HELP_HOWTOUSE;
	mii.dwTypeData = Str_Help_HowToUse;
	InsertMenuItem(hMenu_Help, IDM_HELP_HOWTOUSE, true, &mii);
	mii.wID = IDM_HELP_VERSION;
	mii.dwTypeData = Str_Help_Version;
	InsertMenuItem(hMenu_Help, IDM_HELP_VERSION, true, &mii);

	SetMenu(hWnd, hMenu);
}

void MENU::onWM_COMMAND(HWND hWnd, WPARAM wp)
{
	WPARAM msg = LOWORD(wp);

	switch (msg)
	{
	case IDM_FILE_OPEN:
		PostMessage(hWnd, WM_FILEOPEN, 0, 0);
		return;

	case IDM_FILE_SAVE:
		PostMessage(hWnd, WM_FILESAVE, 0, 0);
		return;

	case IDM_FILE_SAVEAS:
		PostMessage(hWnd, WM_FILESAVEAS, 0, 0);
		return;

	case IDM_FILE_EXIT:
		PostMessage(hWnd, WM_EXIT, 0, 0);
		return;

	case IDM_HELP_HOWTOUSE:
	case IDM_HELP_VERSION:
		return;
	}
}