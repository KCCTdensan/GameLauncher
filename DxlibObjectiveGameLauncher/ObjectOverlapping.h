#pragma once
#include "ButtonObject.h"

template <typename T>
class ObjectOverlapping
{
public:
	static bool Reset() { delete(object); return true; }
	static bool UpdateObject(T* _object); // SetNoMouse() ���\�b�h�������Ă���K�v����

private:
	static T* object;
};
