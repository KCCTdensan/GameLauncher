#pragma once
#include "UUIDGenerator.h"

class ObjectOverlapping
{
public:
	static bool Reset() {
		enforcemented = false;
		guidPrevious = guid;
		guid = "";
		return true;
	}
	static bool UpdateObject(std::string _guid, bool enforcement = false); // SetNoMouse() メソッドを持っている必要あり
	static std::string GetGUID() { return guid; }

private:
	static bool enforcemented;
	static std::string guid;
	static std::string guidPrevious;
};
