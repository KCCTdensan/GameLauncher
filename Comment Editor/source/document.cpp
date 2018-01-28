#include "document.hpp"


DOCUMENT::DOCUMENT()
{
	Contents = { 0 };
}

DOCUMENT::DOCUMENT(CONTENTS Contents)
{
	DOCUMENT::Contents = Contents;
}

bool DOCUMENT::LoadFile(LPCTSTR FilePath)
{
	HANDLE hFile = CreateFile(FilePath, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	ReadFile(hFile, &Contents, sizeof(CONTENTS), NULL, NULL);

	CloseHandle(hFile);

	return true;
}

bool DOCUMENT::SaveFile()
{
	HANDLE hFile = CreateFile(FilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	WriteFile(hFile, &Contents, sizeof(CONTENTS), NULL, NULL);

	CloseHandle(hFile);

	return true;
}

bool DOCUMENT::SaveAsFile(LPCTSTR FilePath)
{
	HANDLE hFile = CreateFile(FilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	WriteFile(hFile, &Contents, sizeof(CONTENTS), NULL, NULL);

	CloseHandle(hFile);

	return true;
}

void DOCUMENT::SetFilePath(LPTSTR FilePath)
{
	for (int i = 0; i < MAX_PATH; i++)
	{
		DOCUMENT::FilePath[i] = FilePath[i];
		if (FilePath[i] == '\0')
		{
			break;
		}
	}
}

CONTENTS DOCUMENT::GetContents()
{
	return Contents;
}

void DOCUMENT::SetContents(const CONTENTS&Contents)
{
	DOCUMENT::Contents = Contents;
}