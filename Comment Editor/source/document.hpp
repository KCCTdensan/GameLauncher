#pragma once

#include <contents.hpp>


class Document
{
	Contents contents;
	TCHAR FilePath[MAX_PATH];

public:
	Document();
	Document(const Contents &contents);
	bool LoadFile(LPCTSTR filePath);
	bool SaveFile();
	bool SaveAsFile(LPCTSTR filePath);
	void SetFilePath(LPTSTR filePath);
	Contents GetContents();
	void SetContents(const Contents &contents);
};