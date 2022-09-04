#pragma once
#include "UUIDGenerator.h"

class ObjectOverlapping
{
public:
	static bool Reset() {
		enforcementedNum = 0;
		guid = "";
		guidCanvas = "";
		return true;
	}
	static bool UpdateObject(std::string _guid, int enforcemented = 1); // SetNoMouse() ���\�b�h�������Ă���K�v����
	static bool UpdateObjectForCanvas(std::string _guid, int enforcemented = 1); // SetNoMouse() ���\�b�h�������Ă���K�v����
	static std::string GetGUID() { return guid; }
	static std::string GetGUIDForCanvas() { return guidCanvas; }

private:
	static int enforcementedNum;
	static std::string guid;
	static std::string guidCanvas;
};
