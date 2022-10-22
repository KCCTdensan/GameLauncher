#include "FontChest.h"

std::map<std::string, int> FontChest::handles;

bool FontChest::CreateFontHandle(std::string handleName, std::string fontName, int fontSize, int fontThick, int fontType)
{
	handles.erase(handleName);
	handles.emplace(handleName, CreateFontToHandle(fontName.c_str(), fontSize, fontThick, fontType));
	return true;
}

int FontChest::GetFontHandle(std::string handleName) {
	auto itr = handles.find(handleName);
	if (itr != handles.end())
		return itr->second; // map‚Ìvalue’l‚Ísecond‚ÉŠi”[
	else
		return -1;
}

bool FontChest::DeleteFontHandle(std::string handleName)
{
	handles.erase(handleName);
	return true;
}
