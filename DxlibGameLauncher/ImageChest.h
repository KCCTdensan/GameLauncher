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
public:
	ImageChest();
	~ImageChest();
	int GetImageHandle(ImageHandleNo handleName);

private:
	int chest[NumImageHandle];
};