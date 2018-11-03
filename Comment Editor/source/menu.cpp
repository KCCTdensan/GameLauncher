#include "menu.hpp"
#include "wmsg.hpp"


namespace menu
{
	enum
	{
		IDM_FILE = 0x00,
		IDM_FILE_NEW,
		IDM_FILE_OPEN,
		IDM_FILE_SAVE,
		IDM_FILE_SAVEAS,
		IDM_FILE_EXIT,
		IDM_HELP,
		IDM_HELP_HOWTOUSE,
		IDM_HELP_VERSION,
	};

	HMENU hMenu;
	HMENU hMenu_File;
	HMENU hMenu_Help;
}


void menu::CreateWndMenu(HWND hWnd)
{
	TCHAR Str_File[] = TEXT("�t�@�C��(&F)");
	TCHAR Str_File_New[] = TEXT("�V�K�쐬(&N)");
	TCHAR Str_File_Open[] = TEXT("�J��(&O)");
	TCHAR Str_File_Save[] = TEXT("�㏑���ۑ�(&S)");
	TCHAR Str_File_SaveAs[] = TEXT("���O��t���ĕۑ�(&A)");
	TCHAR Str_File_Exit[] = TEXT("�I��(&X)");
	TCHAR Str_Help[] = TEXT("�w���v(&H)");
	TCHAR Str_Help_HowToUse[] = TEXT("GEOMETRY�̎g����(&U)");
	TCHAR Str_Help_Version[] = TEXT("�o�[�W�������(&A)");

	MENUITEMINFO mii;

	hMenu = CreateMenu();
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fType = MFT_STRING;

	//�t�@�C��(&F)
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

	//�w���v(&H)
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

void menu::Command(HWND hWnd, WPARAM msg)
{
	switch (msg)
	{
	case IDM_FILE_NEW:
		PostMessage(hWnd, WM_CREATEDOCUMENT, 0, 0);
		return;

	case IDM_FILE_OPEN:
		PostMessage(hWnd, WM_FILENAME_OPEN, 0, 0);
		return;

	case IDM_FILE_SAVE:
		if (SendMessage(hWnd, WM_SAVEDOCUMENT, 0, 0) == -1)
		{
			PostMessage(hWnd, WM_FILENAME_SAVEAS, 0, 0);
		}
		return;

	case IDM_FILE_SAVEAS:
		PostMessage(hWnd, WM_FILENAME_SAVEAS, 0, 0);
		return;

	case IDM_FILE_EXIT:
		DestroyWindow(hWnd);
		return;

	case IDM_HELP_HOWTOUSE:
	case IDM_HELP_VERSION:
		return;
	}
}