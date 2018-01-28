#pragma once

#include <Windows.h>
#include <contents.hpp>

#ifndef INCLUDE_FILE_HPP
#define INCLUDE_FILE_HPP


namespace FILE
{
	bool LoadDocument(HWND hWnd, LPTSTR FilePath);
	bool SaveDocument();
	bool SaveAsDocument(HWND hWnd, LPTSTR FilePath);
	CONTENTS GetContents();
	void SetContents(const CONTENTS&Contents);
}


#endif