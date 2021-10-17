#include "PictureManager.h"

PictureManager::PictureManager()
{
}

int PictureManager::Set(string stg, string path)
{
	for (int i = 0; i < PIC_MAX; i++)
	{
		if (pic[i].ExistenceFlag != FALSE)continue;

		pic[i].ExistenceFlag = TRUE;
		pic[i].name = stg;
		pic[i].handle = LoadGraph(path.c_str());

		break;
	}

	return 0;
}

int PictureManager::Delete(string stg)
{
	return 0;
}

int PictureManager::DeleteAll()
{
	for (int i = 0; i < PIC_MAX; i++)
	{
		if (pic[i].ExistenceFlag != TRUE)continue;
		DeleteGraph(pic[i].handle);
		pic[i].ExistenceFlag = FALSE;
	}

	return 0;
}

int PictureManager::GetHandle(string stg)
{
	for (int i = 0; i < PIC_MAX; i++)
	{
		if (pic[i].ExistenceFlag != TRUE)continue;
		if (stg == pic[i].name) return pic[i].handle;

	}
	return 0;
}
