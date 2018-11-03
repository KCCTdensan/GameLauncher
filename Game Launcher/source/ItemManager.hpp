#pragma once

#include "contents.hpp"
#include <vector>


using namespace std;

struct item_info
{
	contents Contents;
	WCHAR FilePath[MAX_PATH];
};

namespace ItemManager
{
	int ScanItems();
	void ClearItems();
	vector<item_info*> GetItems(category Category);
	bool ExecuteItem(const item_info &Item);
};