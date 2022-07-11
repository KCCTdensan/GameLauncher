#pragma once
#include "UUIDGenerator.h"

class ObjectOverlapping
{
public:
	static bool Reset() {
		guidPrevious = guid;
		guid = "";
		return true;
	}
	static bool UpdateObject(std::string _guid); // SetNoMouse() ���\�b�h�������Ă���K�v����
	static std::string GetGUID() { return guid; }

private:
	static std::string guid;
	static std::string guidPrevious;
};
