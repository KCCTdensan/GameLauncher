#pragma once

#include <Windows.h>

#ifndef INCLUDE_DOCUMENT_HPP
#define INCLUDE_DOCUMENT_HPP


namespace DOCUMENT
{
	void LoadFile(LPCTSTR FilePath, int MaxPath);
	void SaveFile(LPCTSTR FilePath, int MaxPath);
#ifdef MDI
	void CreateDocument(HWND hClientWnd);
#endif
}


#endif