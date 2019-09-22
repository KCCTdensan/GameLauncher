#include "edit.hpp"


namespace edit
{
	enum
	{
		ID_EDIT_FILE = 0x10,
		ID_EDIT_PREVIEW,
		ID_EDIT_TITLE,
		ID_EDIT_CREATOR,
		ID_COMBO_CATEGORY,
		ID_EDIT_GENRE,
		ID_EDIT_LANGUAGE,
		ID_EDIT_ENVIRONMENT,
		ID_EDIT_COMMENT
	};

	const static int CONTROL_LEFT = 200;
	const static int CONTROL_WIDTH = 400;
	const static int EDIT_HEIGHT = 30;
	LPCTSTR PaintText[] = {
		TEXT("実行ファイルのパス"),
		TEXT("プレビュー画像のパス"),
		TEXT("タイトル"),
		TEXT("制作者"),
		TEXT("カテゴリ"),
		TEXT("ジャンル"),
		TEXT("開発言語"),
		TEXT("制作環境"),
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

	Contents contents;
	HWND hEdit_File;
	HWND hEdit_Preview;
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

bool edit::Prepare(HWND hWnd)
{
	hEdit_File = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 30, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_FILE, NULL, NULL);
	hEdit_Preview = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 80, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_PREVIEW, NULL, NULL);
	hEdit_Title = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 130, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_TITLE, NULL, NULL);
	hEdit_Creator = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 180, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_CREATOR, NULL, NULL);
	hCombo_Category = CreateWindow(TEXT("COMBOBOX"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
		CONTROL_LEFT, 230, CONTROL_WIDTH, 300,
		hWnd, (HMENU)ID_COMBO_CATEGORY, NULL, NULL);
	for (int i = 0; i < MAX_CATEGORY; i++)
	{
		SendMessage(hCombo_Category, CB_ADDSTRING, 0, (LPARAM)ComboItem[i]);
	}
	hEdit_Genre = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 280, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_GENRE, NULL, NULL);
	hEdit_Language = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 330, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_LANGUAGE, NULL, NULL);
	hEdit_Environment = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		CONTROL_LEFT, 380, CONTROL_WIDTH, EDIT_HEIGHT,
		hWnd, (HMENU)ID_EDIT_ENVIRONMENT, NULL, NULL);
	hEdit_Comment = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
		CONTROL_LEFT, 430, CONTROL_WIDTH, 200,
		hWnd, (HMENU)ID_EDIT_COMMENT, NULL, NULL);

	return true;
}

void edit::Command(HWND hWnd, WPARAM msg, WPARAM ID)
{
	switch (msg)
	{
	case CBN_SELCHANGE:
		contents.Category = (Category)SendMessage(hCombo_Category, CB_GETCURSEL, 0, 0);
		return;

	case EN_UPDATE:
		switch (ID)
		{
		case ID_EDIT_FILE:
			GetWindowText(hEdit_File, contents.FilePath, MAX_FILEPATH);
			break;

		case ID_EDIT_PREVIEW:
			GetWindowText(hEdit_Preview, contents.PreviewImagePath, MAX_PREVIEWIMAGEPATH);
			break;

		case ID_EDIT_TITLE:
			GetWindowText(hEdit_Title, contents.Title, MAX_TITLE);
			break;

		case ID_EDIT_CREATOR:
			GetWindowText(hEdit_Creator, contents.Creator, MAX_CREATOR);
			break;

		case ID_EDIT_GENRE:
			GetWindowText(hEdit_Genre, contents.Genre, MAX_GENRE);
			break;

		case ID_EDIT_LANGUAGE:
			GetWindowText(hEdit_Language, contents.Language, MAX_LANGUAGE);
			break;

		case ID_EDIT_ENVIRONMENT:
			GetWindowText(hEdit_Environment, contents.Environment, MAX_ENVIRONMENT);
			break;

		case ID_EDIT_COMMENT:
			GetWindowText(hEdit_Comment, contents.Comment, MAX_COMMENT);
			UpdateCommentNumOfWritten(hWnd);
			break;
		}
		return;
	}
}

void edit::Paint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	for (int i = 0; i < 9; i++)
	{
		RECT TextRect = {30, i * 50 + 30, CONTROL_LEFT, i * 50 + 60};
		DrawText(hdc, PaintText[i], lstrlen(PaintText[i]), &TextRect, DT_LEFT | DT_VCENTER);
	}
	DrawCharNumText(hdc, 580, CONTROL_LEFT + CONTROL_WIDTH, Comment_NumOfWritten, MAX_COMMENT - 1);

	EndPaint(hWnd, &ps);
}

Contents edit::GetContents()
{
	return contents;
}

void edit::SetContents(const Contents &contents)
{
	edit::contents = contents;
	SetWindowText(hEdit_File, contents.FilePath);
	SetWindowText(hEdit_Preview, contents.PreviewImagePath);
	SetWindowText(hEdit_Title, contents.Title);
	SetWindowText(hEdit_Creator, contents.Creator);
	SendMessage(hCombo_Category, CB_SETCURSEL, contents.Category, 0);
	SetWindowText(hEdit_Genre, contents.Genre);
	SetWindowText(hEdit_Language, contents.Language);
	SetWindowText(hEdit_Environment, contents.Environment);
	SetWindowText(hEdit_Comment, contents.Comment);
}

void edit::UpdateCommentNumOfWritten(HWND hWnd)
{
	Comment_NumOfWritten = lstrlen(contents.Comment);
	InvalidateRect(hWnd, &TextRect, true);
	UpdateWindow(hWnd);
}

void edit::DrawCharNumText(HDC hdc, int Top, int Right, int NumOfWritten, int Max)
{
	TCHAR Buf[30];
	wsprintf(Buf, TEXT("( %d / %d 文字 )"), NumOfWritten, Max);
	TextRect.top = Top;
	TextRect.right = Right;
	TextRect.left = Right - 150;
	TextRect.bottom = Top + 30;
	DrawText(hdc, Buf, lstrlen(Buf), &TextRect, DT_RIGHT | DT_VCENTER);
}