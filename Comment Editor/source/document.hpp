#pragma once

#include <contents.hpp>

#ifndef INCLUDE_DOCUMENT_HPP
#define INCLUDE_DOCUMENT_HPP


class document
{
	contents Contents;
	TCHAR FilePath[MAX_PATH];

public:
	document();
	document(const contents &Contents);
	bool LoadFile(LPCTSTR FilePath);
	bool SaveFile();
	bool SaveAsFile(LPCTSTR FilePath);
	void SetFilePath(LPTSTR FilePath);
	contents GetContents();
	void SetContents(const contents&Contents);
};


#endif