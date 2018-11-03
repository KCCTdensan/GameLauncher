#include "document.hpp"


document::document()
{
	Contents = { 0 };
}

document::document(const contents &Contents)
{
	document::Contents = Contents;
}

bool document::LoadFile(LPCTSTR FilePath)
{
	HANDLE hFile = CreateFile(FilePath, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	ReadFile(hFile, &Contents, sizeof(contents), NULL, NULL);

	CloseHandle(hFile);

	return true;
}

bool document::SaveFile()
{
	HANDLE hFile = CreateFile(FilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	WriteFile(hFile, &Contents, sizeof(contents), NULL, NULL);

	CloseHandle(hFile);

	return true;
}

bool document::SaveAsFile(LPCTSTR FilePath)
{
	HANDLE hFile = CreateFile(FilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	WriteFile(hFile, &Contents, sizeof(contents), NULL, NULL);

	CloseHandle(hFile);

	return true;
}

void document::SetFilePath(LPTSTR FilePath)
{
	for (int i = 0; i < MAX_PATH; i++)
	{
		document::FilePath[i] = FilePath[i];
		if (FilePath[i] == '\0')
		{
			break;
		}
	}
}

contents document::GetContents()
{
	return Contents;
}

void document::SetContents(const contents&Contents)
{
	document::Contents = Contents;
}