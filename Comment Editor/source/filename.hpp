#pragma once

#include <Windows.h>

#ifndef INCLUDE_FILENAME_HPP
#define INCLUDE_FILENAME_HPP


namespace file_name
{
	bool Open(HWND hWnd);
	bool SaveAs(HWND hWnd);
}


#endif