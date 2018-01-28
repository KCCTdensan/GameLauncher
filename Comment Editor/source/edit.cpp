#include "edit.hpp"


namespace EDIT
{
	enum
	{
		ID_EDIT_TITLE = 0x10,
		ID_EDIT_CREATOR,
		ID_COMBO_CATEGORY,
		ID_EDIT_GENRE,
		ID_EDIT_LANGUAGE,
		ID_EDIT_ENVIRONMENT,
		ID_EDIT_COMMENT
	};

	const static int CONTROL_LEFT = 150;
	const static int CONTROL_WIDTH = 400;
	const static int EDIT_HEIGHT = 30;
	LPCTSTR PaintText[] = {
		TEXT("タイトル"),
		TEXT("制作者"),
		TEXT("カテゴリ"),
		TEXT("ジャンル"),
		TEXT("開発言語"),
		TEXT("開発環境"),
		TEXT("コメント")
	};
	LPCTSTR ComboItem[MAX_CATEGORY] = {
		TEXT("アプリ"),
		TEXT("ゲーム"),
		TEXT("音楽"),
		TEXT("絵"),
		TEXT("3Dモデル"),
		TEXT("動画"),
		TEXT("その他")
	};

	CONTENTS Contents;
	HWND hEdit_Title;
	HWND hEdit_Creator;
	HWND hCombo_Category;
	HWND hEdit_Genre;
	HWND hEdit_Language;
	HWND hEdit_Environment;
	HWND hEdit_Comment;
}

bool EDIT::Prepare(HWND hWnd)
{
	hEdit_Title = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 30, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_TITLE, NULL, NULL);
	hEdit_Creator = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 80, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_CREATOR, NULL, NULL);
	hCombo_Category = CreateWindow(TEXT("COMBOBOX"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
		CONTROL_LEFT, 130, CONTROL_WIDTH, 300,
		hWnd, (HMENU)ID_COMBO_CATEGORY, NULL, NULL);
	for (int i = 0; i < MAX_CATEGORY; i++)
	{
		int ret=SendMessage(hCombo_Category, CB_ADDSTRING, 0, (LPARAM)ComboItem[i]);
	}
	hEdit_Genre = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 180, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_GENRE, NULL, NULL);
	hEdit_Language = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 230, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_LANGUAGE, NULL, NULL);
	hEdit_Environment = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 280, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_ENVIRONMENT, NULL, NULL);
	hEdit_Comment = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
		CONTROL_LEFT, 330, CONTROL_WIDTH, 200,
		hWnd, (HMENU)ID_EDIT_COMMENT, NULL, NULL);

	return true;
}

void EDIT::Command(WPARAM msg, WPARAM ID)
{
	switch (msg)
	{
	case EN_UPDATE:
		switch (ID)
		{
		case ID_EDIT_TITLE:
			GetWindowText(hEdit_Title, Contents.Title, MAX_TITLE);
			break;

		case ID_EDIT_CREATOR:
			GetWindowText(hEdit_Creator, Contents.Creator, MAX_CREATOR);
			break;

		case ID_EDIT_GENRE:
			GetWindowText(hEdit_Genre, Contents.Genre, MAX_GENRE);
			break;

		case ID_EDIT_LANGUAGE:
			GetWindowText(hEdit_Language, Contents.Language, MAX_LANGUAGE);
			break;

		case ID_EDIT_ENVIRONMENT:
			GetWindowText(hEdit_Environment, Contents.Environment, MAX_ENVIRONMENT);
			break;

		case ID_EDIT_COMMENT:
			GetWindowText(hEdit_Comment, Contents.Comment, MAX_COMMENT);
			break;
		}
		return;

	case CBN_SELCHANGE:
		Contents.Category = (CATEGORY)SendMessage(hCombo_Category, CB_GETCURSEL, 0, 0);
		return;
	}
}

void EDIT::Paint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	for (int i = 0; i < 7; i++)
	{
		RECT TextRect = { 50,i * 50 + 30,CONTROL_LEFT,i * 50 + 60 };
		DrawText(hdc, PaintText[i], lstrlen(PaintText[i]), &TextRect, DT_LEFT | DT_VCENTER);
	}

	EndPaint(hWnd, &ps);
}

CONTENTS EDIT::GetContents()
{
	return Contents;
}

void EDIT::SetContents(const CONTENTS&Contents)
{
	EDIT::Contents = Contents;
	SetWindowText(hEdit_Title, Contents.Title);
	SetWindowText(hEdit_Creator, Contents.Creator);
	SendMessage(hCombo_Category, CB_SETCURSEL, Contents.Category, 0);
	SetWindowText(hEdit_Genre, Contents.Genre);
	SetWindowText(hEdit_Language, Contents.Language);
	SetWindowText(hEdit_Environment, Contents.Environment);
	SetWindowText(hEdit_Comment, Contents.Comment);
}