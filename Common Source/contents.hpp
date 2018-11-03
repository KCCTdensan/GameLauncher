#pragma once

#include <Windows.h>


enum category
{
	CAT_APP,
	CAT_GAME,
	CAT_MUSIC,
	CAT_PICTURE,
	CAT_3DMODEL,
	CAT_VIDEO,
	CAT_OTHERS,
	MAX_CATEGORY
};

const static int MAX_HEADER = 64;
const static int MAX_FILEPATH = MAX_PATH;
const static int MAX_PREVIEWIMAGEPATH = MAX_PATH;
const static int MAX_TITLE = 32;
const static int MAX_CREATOR = 32;
const static int MAX_GENRE = 32;
const static int MAX_LANGUAGE = 32;
const static int MAX_ENVIRONMENT = 32;
const static int MAX_COMMENT = 1024;

struct contents
{
	WCHAR Header[MAX_HEADER] = L"Comment Editor for KCCT Launcher 1.0.0.b";
	WCHAR FilePath[MAX_FILEPATH];
	WCHAR PreviewImagePath[MAX_PREVIEWIMAGEPATH];
	WCHAR Title[MAX_TITLE];
	WCHAR Creator[MAX_CREATOR];
	category Category;
	WCHAR Genre[MAX_GENRE];
	WCHAR Language[MAX_LANGUAGE];
	WCHAR Environment[MAX_ENVIRONMENT];
	WCHAR Comment[MAX_COMMENT];
};