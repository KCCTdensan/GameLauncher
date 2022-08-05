#include "ObjectOverlapping.h"

std::string ObjectOverlapping::guid = "";
std::string ObjectOverlapping::guidPrevious = "";

bool ObjectOverlapping::UpdateObject(std::string _guid)
{
	guid = _guid;
	return true;
}