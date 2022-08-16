#include "ObjectOverlapping.h"

std::string ObjectOverlapping::guid = "";
std::string ObjectOverlapping::guidPrevious = "";
int ObjectOverlapping::enforcementedNum = 0;

bool ObjectOverlapping::UpdateObject(std::string _guid, int enforcement)
{
	if (enforcementedNum > enforcement) return false;
	enforcementedNum = enforcement;
	guid = _guid;
	return true;
}