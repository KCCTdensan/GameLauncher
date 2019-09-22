#include "document.hpp"


Document::Document()
	: contents {0}
{

}

Document::Document(const Contents &contents)
{
	this->contents = contents;
}

bool Document::LoadFile(LPCTSTR FilePath)
{
	HANDLE hFile = CreateFile(FilePath, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	ReadFile(hFile, &contents, sizeof(Contents), NULL, NULL);

	CloseHandle(hFile);

	return true;
}

bool Document::SaveFile()
{
	HANDLE hFile = CreateFile(FilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	WriteFile(hFile, &contents, sizeof(Contents), NULL, NULL);

	CloseHandle(hFile);

	return true;
}

bool Document::SaveAsFile(LPCTSTR filePath)
{
	HANDLE hFile = CreateFile(filePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	WriteFile(hFile, &contents, sizeof(Contents), NULL, NULL);

	CloseHandle(hFile);

	return true;
}

void Document::SetFilePath(LPTSTR FilePath)
{
	for (int i = 0; i < MAX_PATH; i++)
	{
		Document::FilePath[i] = FilePath[i];
		if (FilePath[i] == '\0')
		{
			break;
		}
	}
}

Contents Document::GetContents()
{
	return contents;
}

void Document::SetContents(const Contents &contents)
{
	this->contents = contents;
}