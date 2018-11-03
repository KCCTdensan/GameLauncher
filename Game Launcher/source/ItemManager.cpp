#include "ItemManager.hpp"


namespace ItemManager
{
	vector<item_info*> Items[MAX_CATEGORY];

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
		item_info *Info = new item_info;
		HANDLE hFile = CreateFile(FilePath.c_str(), GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		ReadFile(hFile, &Info->Contents, sizeof(contents), NULL, NULL);
		FilePath.copy(Info->FilePath, FilePath.length());
		Items[Info->Contents.Category].push_back(Info);
		CloseHandle(hFile);
	}

	void ScanDirectory(wstring FilePath)
	{
		HANDLE hFind;
		WIN32_FIND_DATA wfd = {};
		wstring exception1 = L".";
		wstring exception2 = L"..";
		hFind = FindFirstFile((FilePath + L'*').c_str(), &wfd);
		if(hFind == INVALID_HANDLE_VALUE)
		{
			return;
		}
		do
		{
			if (exception1 == wfd.cFileName || exception2 == wfd.cFileName)
			{
				continue;
			}
			if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				ScanDirectory(FilePath + wfd.cFileName + L'/');
			}
			else
			{
				wstring FileName = wfd.cFileName;
				wstring Ex = FileName.substr(FileName.length() - 4, 4);
				if (L".apc" != Ex)
				{
					continue;
				}
				LoadItem(FilePath + FileName);
			}
		} while(FindNextFile(hFind, &wfd));
		FindClose(hFind);
	}
	
	int ScanItems()
	{
		ClearItems();
		ScanDirectory(L"Works/");
		return 0;
	}

	vector<item_info*> GetItems(category Category)
	{
		return Items[Category];
	}

	bool ExecuteItem(const item_info &Item)
	{
		STARTUPINFO si = {};
		si.cb = sizeof(STARTUPINFO);
		PROCESS_INFORMATION pi = {};
		wstring Directory = Item.FilePath;
		while (Directory.back() != L'/')
		{
			Directory.pop_back();
		}
		Directory += Item.Contents.FilePath;
		WCHAR CommandLine[MAX_PATH];
		int i = -1;
		do
		{
			i++;
			CommandLine[i] = Directory[i];
		} while (Directory[i] != L'\0');
		switch (Item.Contents.Category)
		{
		case CAT_APP:
		case CAT_GAME:
			BOOL Ret = CreateProcess(CommandLine, NULL, NULL, NULL, false, NULL, NULL, NULL, &si, &pi);
			return Ret != 0;
		}
		return false;
	}
}