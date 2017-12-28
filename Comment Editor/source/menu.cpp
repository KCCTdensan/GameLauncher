#include "menu.hpp"
#include "wmsg.h"


enum
{
	IDM_FILE,
	IDM_FILE_NEW,
	IDM_FILE_OPEN,
	IDM_FILE_SAVE,
	IDM_FILE_SAVEAS,
	IDM_FILE_EXIT,
	IDM_HELP,
	IDM_HELP_HOWTOUSE,
	IDM_HELP_VERSION,
#ifdef MDI
	IDM_EDIT
#endif
};


namespace MENU
{
	HMENU hMenu;
	HMENU hMenu_File;
	HMENU hMenu_Help;
#ifdef MDI
	HMENU hMenu_Edit;
#endif
}


void MENU::CreateWndMenu(HWND hWnd)
{
	TCHAR Str_File[] = TEXT("ファイル(&F)");
	TCHAR Str_File_New[] = TEXT("新規作成(&N)");
	TCHAR Str_File_Open[] = TEXT("開く(&O)");
	TCHAR Str_File_Save[] = TEXT("上書き保存(&S)");
	TCHAR Str_File_SaveAs[] = TEXT("名前を付けて保存(&A)");
	TCHAR Str_File_Exit[] = TEXT("終了(&X)");
	TCHAR Str_Help[] = TEXT("ヘルプ(&H)");
	TCHAR Str_Help_HowToUse[] = TEXT("GEOMETRYの使い方(&U)");
	TCHAR Str_Help_Version[] = TEXT("バージョン情報(&A)");
	TCHAR Str_Edit[] = TEXT("編集中のドキュメント(&E)");

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
	mii.wID = IDM_FILE_NEW;
	mii.dwTypeData = Str_File_New;
	InsertMenuItem(hMenu_File, IDM_FILE_NEW, true, &mii);
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

#ifdef MDI
	hMenu_Edit = CreateMenu();
	mii.fMask = MIIM_TYPE | MIIM_SUBMENU | MIIM_ID;
	mii.wID = IDM_EDIT;
	mii.hSubMenu = hMenu_Edit;
	mii.dwTypeData = Str_Edit;
	InsertMenuItem(hMenu, IDM_EDIT, true, &mii);
#endif

	SetMenu(hWnd, hMenu);
}

void MENU::onWM_COMMAND(HWND hWnd, WPARAM wp)
{
	WPARAM msg = LOWORD(wp);

	switch (msg)
	{
	case IDM_FILE_NEW:
		PostMessage(hWnd, WM_CREATEDOCUMENT, 0, 0);
		return;

	case IDM_FILE_OPEN:
		PostMessage(hWnd, WM_FILE_OPEN, 0, 0);
		return;

	case IDM_FILE_SAVE:
		PostMessage(hWnd, WM_FILE_SAVE, 0, 0);
		return;

	case IDM_FILE_SAVEAS:
		PostMessage(hWnd, WM_FILE_SAVEAS, 0, 0);
		return;

	case IDM_FILE_EXIT:
		DestroyWindow(hWnd);
		return;

	case IDM_HELP_HOWTOUSE:
	case IDM_HELP_VERSION:
		return;
	}
}

#ifdef MDI

HMENU MENU::GetEditMenuHandle()
{
	return hMenu_Edit;
}

#endif