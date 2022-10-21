#pragma once
#include <windows.h>
#include <tchar.h>

class ExePath 
{
public:

	ExePath();
	~ExePath() {}

	const TCHAR* GetPath() const
	{
		return m_Path;
	}

protected:
	TCHAR m_Path[MAX_PATH];
};
