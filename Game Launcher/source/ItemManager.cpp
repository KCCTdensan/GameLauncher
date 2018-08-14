#include "ItemManager.hpp"


namespace ItemManager
{
	vector<ItemInfo*> Items[MAX_CATEGORY];

	void ClearItems()
	{
		for(int i = 0; i < MAX_CATEGORY; ++i)
		{
			int NumItems = (int)Items[i].size();
			for(int j = 0; j < NumItems; ++j)
			{
				delete Items[i][j];
			}
			Items[i].clear();
		}
	}

	void LoadItem(wstring FilePath)
	{
		ItemInfo *Info = new ItemInfo;
		HANDLE hFile = CreateFile(FilePath.c_str(), GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		ReadFile(hFile, &Info->Contents, sizeof(CONTENTS), NULL, NULL);
		FilePath.copy(Info->FileName, FilePath.length());
		Items[Info->Contents.Category].push_back(Info);
		CloseHandle(hFile);
	}

	void Directory(wstring FilePath)
	{
		HANDLE hFind;
		WIN32_FIND_DATA wfd;
		wstring StrFile = FilePath;
		wstring exception1 = L".";
		wstring exception2 = L"..";
		StrFile += L"*.apc";
		hFind = FindFirstFile(StrFile.c_str(), &wfd);
		if(hFind == INVALID_HANDLE_VALUE)
		{
			return;
		}
		do
		{
			if((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (exception1 != wfd.cFileName && exception2 != wfd.cFileName))
			{
				FilePath += L"/";
				FilePath += wfd.cFileName;
				Directory(FilePath);
			}
			else
			{
				FilePath += L"/";
				FilePath += wfd.cFileName;
				LoadItem(FilePath);
			}
		} while(FindNextFile(hFind, &wfd));
		FindClose(hFind);
	}
	
	int ScanItems()
	{
		ClearItems();
		Directory(L"./");
		return 0;
	}

	vector<ItemInfo*> GetItems(CATEGORY Category)
	{
		return Items[Category];
	}

}