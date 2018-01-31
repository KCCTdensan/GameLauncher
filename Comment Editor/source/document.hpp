#pragma once

#include <contents.hpp>

#ifndef INCLUDE_DOCUMENT_HPP
#define INCLUDE_DOCUMENT_HPP


class DOCUMENT
{
	CONTENTS Contents;
	TCHAR FilePath[MAX_PATH];

public:
	DOCUMENT();
	DOCUMENT(CONTENTS Contents);
	bool LoadFile(LPCTSTR FilePath);
	bool SaveFile();
	bool SaveAsFile(LPCTSTR FilePath);
	void SetFilePath(LPTSTR FilePath);
	CONTENTS GetContents();
	void SetContents(const CONTENTS&Contents);
};


#endif