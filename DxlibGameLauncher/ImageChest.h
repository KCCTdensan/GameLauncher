#pragma once

#include <DxLib.h>
#include "OperationData.h"
#include <unordered_map>


enum ImageHandleNo
{
	a,//add handle name
	NumImageHandle
};

class ImageChest
{
	int chest[NumImageHandle];

public:
	ImageChest();
	~ImageChest();
	int GetImageHandle(ImageHandleNo handleName);
};