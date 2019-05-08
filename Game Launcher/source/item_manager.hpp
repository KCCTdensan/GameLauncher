#pragma once

#include <vector>
#include <string>
#include "contents.hpp"


struct ItemInfo
{
	Contents contents;
	WCHAR filePath[MAX_PATH];
};

class ItemManager
{
	std::vector<ItemInfo*> items[MAX_CATEGORY];

	bool scanDirectory(std::wstring filePath);
	bool loadItem(std::wstring filePath);
	bool executeProgram(std::wstring filePath);
	bool executeExplorer(std::wstring directoryPath);

public:
	int scanItems(std::wstring directoryPath);
	void clearItems();
	std::vector<ItemInfo*> getItems(Category category);
	bool executeItem(const ItemInfo &item);
};