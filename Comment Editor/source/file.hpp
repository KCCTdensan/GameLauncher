#pragma once

#include <Windows.h>
#include <contents.hpp>

#ifndef INCLUDE_FILE_HPP
#define INCLUDE_FILE_HPP


namespace FILE
{
	void LoadDocument(HWND hWnd, LPTSTR FilePath);
	void SaveDocument();
	void SaveAsDocument(HWND hWnd, LPTSTR FilePath);
	CONTENTS GetContents();
	void SetContents(const CONTENTS&Contents);
}


#endif