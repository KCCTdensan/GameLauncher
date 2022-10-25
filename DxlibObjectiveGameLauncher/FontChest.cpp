#include "FontChest.h"

std::map<std::string, int> FontChest::handles;

bool FontChest::CreateFontHandle(std::string handleName, std::string fontName, int fontSize, int fontThick, int fontType)
{
	auto itr = handles.find(handleName);
	if (itr != handles.end()) {
		DeleteFontToHandle(itr->second);
	}
	handles.erase(handleName);
	int value = CreateFontToHandle(fontName.c_str(), fontSize, fontThick, fontType);
	printfDx("%d, %s\n", value, handleName.c_str());
	handles.emplace(handleName, value);
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
	auto itr = handles.find(handleName);
	if (itr != handles.end())
		DeleteFontToHandle(itr->second); // map‚Ìvalue’l‚Ísecond‚ÉŠi”[
	handles.erase(handleName);
	return true;
}
