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

	bool ExecuteProgram(LPCTSTR DirectoryPath, LPCTSTR FilePath)
	{
		STARTUPINFO si = {};
		si.cb = sizeof(STARTUPINFO);
		PROCESS_INFORMATION pi = {};
		WCHAR CurrentDirectoryPrev[MAX_PATH];
		WCHAR Directory[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, CurrentDirectoryPrev);
		SetCurrentDirectory(DirectoryPath);
		GetCurrentDirectory(MAX_PATH, Directory);
		SetCurrentDirectory(CurrentDirectoryPrev);
		bool Ret = CreateProcess(FilePath, L"", NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, Directory, &si, &pi) != 0;
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		return Ret;
	}

	bool ExecuteExplorer(LPCTSTR DirectoryPath)
	{
		ShellExecute(NULL, L"open", DirectoryPath, NULL, NULL, SW_SHOWNORMAL);
		return true;
	}

	bool ExecuteItem(const item_info &Item)
	{
		wstring Directory = Item.FilePath;
		while (Directory.back() != L'/')
		{
			Directory.pop_back();
		}

		switch (Item.Contents.Category)
		{
		case CAT_APP:
		case CAT_GAME:
			Directory.pop_back();
			return ExecuteProgram(Directory.c_str(), (Directory + Item.Contents.FilePath).c_str());

		case CAT_OTHERS:
			Directory.pop_back();
			return ExecuteExplorer(Directory.c_str());
		}
		return false;
	}
}