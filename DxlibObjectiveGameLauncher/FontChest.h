#pragma once
#include <string>
#include <map>
#include "DxLib.h"

class FontChest
{
public:
	static bool CreateFontHandle(std::string handleName, std::string fontName, int fontSize, int fontThick = -1, int fontType = DX_FONTTYPE_ANTIALIASING);
	static int GetFontHandle(std::string handleName);

	static bool DeleteFontHandle(std::string handleName);

private:
	static std::map<std::string, int> handles;
};

