#include "FontData.h"

std::map<std::string, int> FontData::handles;

bool FontData::CreateFontHandle(std::string handleName, std::string fontName, int fontSize, int fontThick, int fontType)
{
	handles.emplace(handleName, CreateFontToHandle(fontName.c_str(), fontSize, fontThick, fontType));
	return true;
}

int FontData::GetFontHandle(std::string handleName) {
	auto itr = handles.find(handleName);
	if (itr != handles.end())
		return itr->second; // map‚Ìvalue’l‚Ísecond‚ÉŠi”[
	else
		return -1;
}