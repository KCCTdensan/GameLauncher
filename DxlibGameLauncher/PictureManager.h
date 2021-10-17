#include "DxLib.h"
#include <array>
#include <string>
#include "PictureData.h"

#pragma once


using namespace std;

constexpr int PIC_MAX = 64;

class PictureManager
{
public:
	PictureManager();
	int Set(string stg, string path);
	int Delete(string stg);
	int DeleteAll();

	int GetHandle(string stg);

private:

	std::array<PictureData, PIC_MAX> pic;
	int playingHandle;
};