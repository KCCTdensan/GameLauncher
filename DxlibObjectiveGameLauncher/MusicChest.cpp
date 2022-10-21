#include "MusicChest.h"

std::map<std::string, int> MusicChest::handles;

bool MusicChest::CreateMusicHandle(std::string handleName, std::string filePath)
{
	int handle = LoadSoundMem(filePath.c_str());
	if (handle == -1) return false;
	handles.erase(handleName);
	handles.emplace(handleName, handle);
	return true;
}

int MusicChest::GetMusicHandle(std::string handleName)
{
	auto itr = handles.find(handleName);
	if (itr != handles.end())
		return itr->second; // map‚Ìvalue’l‚Ísecond‚ÉŠi”[
	else
		return -1;
}

bool MusicChest::DeleteMusicHandle(std::string handleName)
{
	handles.erase(handleName);
	return true;
}
