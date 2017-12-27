#pragma once

#include <Windows.h>

#ifndef INCLUDE_FILE_HPP
#define INCLUDE_FILE_HPP


namespace FILE
{
	void Load(LPCTSTR FilePath, int MaxPath);
	void Save(LPCTSTR FilePath, int MaxPath);
}


#endif