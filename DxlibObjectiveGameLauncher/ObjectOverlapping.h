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
	static bool UpdateObject(std::string _guid); // SetNoMouse() メソッドを持っている必要あり
	static std::string GetGUID() { return guid; }

private:
	static std::string guid;
	static std::string guidPrevious;
};
