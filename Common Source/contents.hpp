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

const static int MAX_TITLE = 32;
const static int MAX_CREATOR = 32;
const static int MAX_GENRE = 32;
const static int MAX_LANGUAGE = 32;
const static int MAX_IDEORDAW = 32;
const static int MAX_COMMENT = 1024;

struct CONTENTS
{
	TCHAR Title[MAX_TITLE];
	TCHAR Creator[MAX_CREATOR];
	CATEGORY Category;
	TCHAR Genre[MAX_GENRE];
	TCHAR Language[MAX_LANGUAGE];
	TCHAR IDEorDAW[MAX_IDEORDAW];
	TCHAR Comment[MAX_COMMENT];
};