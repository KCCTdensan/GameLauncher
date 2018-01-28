#pragma once

#include <Windows.h>


enum CATEGORY
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
const static int MAX_TITLE = 32;
const static int MAX_CREATOR = 32;
const static int MAX_GENRE = 32;
const static int MAX_LANGUAGE = 32;
const static int MAX_ENVIRONMENT = 32;
const static int MAX_COMMENT = 1024;

struct CONTENTS
{
	WCHAR Header[MAX_HEADER] = L"KCCT Lancher Comment Editor 1.0.0";
	WCHAR Title[MAX_TITLE];
	WCHAR Creator[MAX_CREATOR];
	CATEGORY Category;
	WCHAR Genre[MAX_GENRE];
	WCHAR Language[MAX_LANGUAGE];
	WCHAR Environment[MAX_ENVIRONMENT];
	WCHAR Comment[MAX_COMMENT];
};