#include "item_manager.hpp"


bool ItemManager::scanDirectory(std::wstring filePath)
{
	WIN32_FIND_DATA wfd = {};
	std::wstring exception1 = L".";
	std::wstring exception2 = L"..";

	HANDLE hFind = FindFirstFile((filePath + L'*').c_str(), &wfd);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	do
	{
		if(exception1 == wfd.cFileName || exception2 == wfd.cFileName)
		{
			continue;
		}
		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			scanDirectory(filePath + wfd.cFileName + L'/');
		}
		else
		{
			std::wstring fileName = wfd.cFileName;
			std::wstring extension = fileName.substr(fileName.length() - 4, 4);
			if(L".apc" != extension)
			{
				continue;
			}
			loadItem(filePath + fileName);
		}
	} while(FindNextFile(hFind, &wfd));
	FindClose(hFind);
	return true;
}

bool ItemManager::loadItem(std::wstring filePath)
{
	ItemInfo *itemInfo = new ItemInfo;
	HANDLE hFile = CreateFile(filePath.c_str(), GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	ReadFile(hFile, &itemInfo->contents, sizeof(Contents), NULL, NULL);
	filePath.copy(itemInfo->filePath, filePath.length());
	items[itemInfo->contents.Category].push_back(itemInfo);
	CloseHandle(hFile);
	return true;
}

int ItemManager::scanItems(std::wstring directoryPath)
{
	clearItems();
	scanDirectory(L"Works/");
	return 0;
}

void ItemManager::clearItems()
{
	for(int i = 0; i < MAX_CATEGORY; ++i)
	{
		int numItems = (int)items[i].size();
		for(int j = 0; j < numItems; ++j)
		{
			delete items[i][j];
		}
		items[i].clear();
	}
}

std::vector<ItemInfo*> ItemManager::getItems(Category category)
{
	return items[category];
}

bool ItemManager::executeItem(const ItemInfo &item)
{
	std::wstring directoryPath = item.filePath;
	while(directoryPath.back() != L'/')
	{
		directoryPath.pop_back();
	}

	switch(item.contents.Category)
	{
	case CAT_APP:
	case CAT_GAME:
		directoryPath.pop_back();
		return executeProgram(item.filePath);

	case CAT_OTHERS:
		directoryPath.pop_back();
		return executeExplorer(directoryPath);
	}
	return false;
}

bool ItemManager::executeProgram(std::wstring filePath)
{
	std::wstring directoryPath = filePath;
	while(directoryPath.back() != L'/')
	{
		directoryPath.pop_back();
	}
	STARTUPINFO si = {};
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi = {};
	/*WCHAR currentDirectory[MAX_PATH];
	WCHAR Directory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDirectory);
	SetCurrentDirectory(directoryPath);
	GetCurrentDirectory(MAX_PATH, Directory);
	SetCurrentDirectory(currentDirectory);*/
	bool ret = CreateProcess(filePath.c_str(), L"", NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, directoryPath.c_str(), &si, &pi) != 0;
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	return ret;
}

bool ItemManager::executeExplorer(std::wstring directoryPath)
{
	ShellExecute(NULL, L"open", directoryPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
	return true;
}