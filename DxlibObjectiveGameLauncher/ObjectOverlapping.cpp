#include "ObjectOverlapping.h"

std::string ObjectOverlapping::guid = "";
std::string ObjectOverlapping::guidPrevious = "";
bool ObjectOverlapping::enforcemented = false;

bool ObjectOverlapping::UpdateObject(std::string _guid, bool enforcement)
{
	if (enforcemented) return false;
	if (enforcement) enforcemented = true;
	guid = _guid;
	return true;
}