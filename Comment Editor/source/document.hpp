#pragma once

#include <contents.hpp>

#ifndef INCLUDE_DOCUMENT_HPP
#define INCLUDE_DOCUMENT_HPP


class DOCUMENT
{
	contents Contents;
	TCHAR FilePath[MAX_PATH];

public:
	DOCUMENT();
	DOCUMENT(contents Contents);
	bool LoadFile(LPCTSTR FilePath);
	bool SaveFile();
	bool SaveAsFile(LPCTSTR FilePath);
	void SetFilePath(LPTSTR FilePath);
	contents GetContents();
	void SetContents(const contents&Contents);
};


#endif