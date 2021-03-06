#include "ImageChest.h"


namespace
{
	const static TCHAR *ImagePath[] = {
		TEXT("")//add image file path
	};
}

ImageChest::ImageChest()
{
	for(int i = 0; i < NumImageHandle; ++i)
	{
		chest[i] = LoadGraph(ImagePath[i]);
	}
}

ImageChest::~ImageChest()
{
	for(int i = 0; i < NumImageHandle; ++i)
	{
		DeleteGraph(chest[i]);
		chest[i] = 0;
	}
}

int ImageChest::GetImageHandle(ImageHandleNo handleName)
{
	return chest[handleName];
}
