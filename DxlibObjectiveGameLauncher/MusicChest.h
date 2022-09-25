#pragma once
#include <string>
#include <map>
#include "DxLib.h"

class MusicChest
{
public:
	static bool CreateMusicHandle(std::string handleName, std::string filePath);
	static int GetMusicHandle(std::string handleName);

	static bool DeleteMusicHandle(std::string handleName);

private:
	static std::map<std::string, int> handles;
};

