#pragma once
#include <string>
#include <map>
#include "DxLib.h"
#include "PositionVector.h"

class ImageChest // BMP,JPEG,PNG,DDS,ARGB,TGA
{
public:
	static bool CreateImageHandle(std::string handleName, std::string filePath);
	static int GetImageHandle(std::string handleName);
	static PosVec GetImageSize(std::string handleName);

	static bool DeleteImageHandle(std::string handleName);

	static bool ResizeImage(std::string handleName, PosVec newSize);

private:
	static std::map<std::string, int> handles;
};

