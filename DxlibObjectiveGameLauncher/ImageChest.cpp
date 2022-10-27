#include "ImageChest.h"

std::map<std::string, int> ImageChest::handles;

bool ImageChest::CreateImageHandle(std::string handleName, std::string filePath)
{
	auto itr = handles.find(handleName);
	if (itr != handles.end()) return false;
	int handle = LoadGraph(filePath.c_str());
	if (handle == -1) return false;
	handles.erase(handleName);
	handles.emplace(handleName, handle);
	return true;
}

int ImageChest::GetImageHandle(std::string handleName)
{
	auto itr = handles.find(handleName);
	if (itr != handles.end())
		return itr->second; // map‚Ìvalue’l‚Ísecond‚ÉŠi”[
	else
		return -1;
}

PosVec ImageChest::GetImageSize(std::string handleName)
{
	PosVec ans;
	auto itr = handles.find(handleName);
	if (itr != handles.end()) {
		GetGraphSizeF(itr->second, &ans.x, &ans.y);
		return ans;
	}
	else
		return ans;
}

bool ImageChest::DeleteImageHandle(std::string handleName)
{
	DeleteGraph(GetImageHandle(handleName));
	handles.erase(handleName);
	return true;
}

bool ImageChest::ResizeImage(std::string handleName, PosVec newSize)
{
	return false;
}
