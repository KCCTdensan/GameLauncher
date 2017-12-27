#include "file.hpp"
#include "contents.hpp"


void FILE::Load(LPCTSTR FilePath, int MaxPath)
{
	CONTENTS Buf;

	HANDLE hFile = CreateFile(FilePath, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, &Buf, sizeof(CONTENTS), NULL, NULL);

	CloseHandle(hFile);
}

void FILE::Save(LPCTSTR FilePath, int MaxPath)
{
	CONTENTS Buf;

	HANDLE hFile = CreateFile(FilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	WriteFile(hFile, &Buf, sizeof(CONTENTS), NULL, NULL);

	CloseHandle(hFile);
}