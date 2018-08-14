#pragma once

#include "contents.hpp"
#include <vector>


using namespace std;

struct ItemInfo
{
	CONTENTS Contents;
	WCHAR FileName[MAX_PATH];
};

namespace ItemManager
{
	int ScanItems();
	void ClearItems();
	vector<ItemInfo*> GetItems(CATEGORY Category);
};