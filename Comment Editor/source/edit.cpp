#include "edit.hpp"


namespace EDIT
{
	enum
	{
		ID_EDIT_FILE = 0x10,
		ID_EDIT_TITLE,
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
		TEXT("�t�@�C����"),
		TEXT("�^�C�g��"),
		TEXT("�����"),
		TEXT("�J�e�S��"),
		TEXT("�W������"),
		TEXT("�J������"),
		TEXT("�����"),
		TEXT("�R�����g")
	};
	LPCTSTR ComboItem[MAX_CATEGORY] = {
		TEXT("�A�v��"),
		TEXT("�Q�[��"),
		TEXT("���y"),
		TEXT("�G"),
		TEXT("3D���f��"),
		TEXT("����"),
		TEXT("���̑�")
	};

	contents Contents;
	HWND hEdit_File;
	HWND hEdit_Title;
	HWND hEdit_Creator;
	HWND hCombo_Category;
	HWND hEdit_Genre;
	HWND hEdit_Language;
	HWND hEdit_Environment;
	HWND hEdit_Comment;
	RECT TextRect;
	int Comment_NumOfWritten;

	void DrawCharNumText(HDC hdc, int Top, int Right, int NumOfWritten, int Max);
}

bool EDIT::Prepare(HWND hWnd)
{
	hEdit_File = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 30, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_FILE, NULL, NULL);
	hEdit_Title = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 80, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_TITLE, NULL, NULL);
	hEdit_Creator = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 130, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_CREATOR, NULL, NULL);
	hCombo_Category = CreateWindow(TEXT("COMBOBOX"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
		CONTROL_LEFT, 180, CONTROL_WIDTH, 300,
		hWnd, (HMENU)ID_COMBO_CATEGORY, NULL, NULL);
	for (int i = 0; i < MAX_CATEGORY; i++)
	{
		SendMessage(hCombo_Category, CB_ADDSTRING, 0, (LPARAM)ComboItem[i]);
	}
	hEdit_Genre = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 230, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_GENRE, NULL, NULL);
	hEdit_Language = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 280, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_LANGUAGE, NULL, NULL);
	hEdit_Environment = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 330, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_ENVIRONMENT, NULL, NULL);
	hEdit_Comment = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
		CONTROL_LEFT, 380, CONTROL_WIDTH, 200,
		hWnd, (HMENU)ID_EDIT_COMMENT, NULL, NULL);

	return true;
}

void EDIT::Command(HWND hWnd, WPARAM msg, WPARAM ID)
{
	switch (msg)
	{
	case CBN_SELCHANGE:
		Contents.Category = (category)SendMessage(hCombo_Category, CB_GETCURSEL, 0, 0);
		return;

	case EN_UPDATE:
		switch (ID)
		{
		case ID_EDIT_FILE:
			GetWindowText(hEdit_File, Contents.File, MAX_FILE);
			break;

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
			UpdateCommentNumOfWritten(hWnd);
			break;
		}
		return;
	}
}

void EDIT::Paint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	for (int i = 0; i < 8; i++)
	{
		RECT TextRect = { 50,i * 50 + 30,CONTROL_LEFT,i * 50 + 60 };
		DrawText(hdc, PaintText[i], lstrlen(PaintText[i]), &TextRect, DT_LEFT | DT_VCENTER);
	}
	DrawCharNumText(hdc, 580, CONTROL_LEFT + CONTROL_WIDTH, Comment_NumOfWritten, MAX_COMMENT - 1);

	EndPaint(hWnd, &ps);
}

contents EDIT::GetContents()
{
	return Contents;
}

void EDIT::SetContents(const contents&Contents)
{
	EDIT::Contents = Contents;
	SetWindowText(hEdit_File, Contents.File);
	SetWindowText(hEdit_Title, Contents.Title);
	SetWindowText(hEdit_Creator, Contents.Creator);
	SendMessage(hCombo_Category, CB_SETCURSEL, Contents.Category, 0);
	SetWindowText(hEdit_Genre, Contents.Genre);
	SetWindowText(hEdit_Language, Contents.Language);
	SetWindowText(hEdit_Environment, Contents.Environment);
	SetWindowText(hEdit_Comment, Contents.Comment);
}

void EDIT::UpdateCommentNumOfWritten(HWND hWnd)
{
	Comment_NumOfWritten = lstrlen(Contents.Comment);
	InvalidateRect(hWnd, &TextRect, true);
	UpdateWindow(hWnd);
}

void EDIT::DrawCharNumText(HDC hdc, int Top, int Right, int NumOfWritten, int Max)
{
	TCHAR Buf[30];
	wsprintf(Buf, TEXT("( %d / %d ���� )"), NumOfWritten, Max);
	TextRect.top = Top;
	TextRect.right = Right;
	TextRect.left = Right - 150;
	TextRect.bottom = Top + 30;
	DrawText(hdc, Buf, lstrlen(Buf), &TextRect, DT_RIGHT | DT_VCENTER);
}