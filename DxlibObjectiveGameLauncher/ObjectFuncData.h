#pragma once
#include "ObjectBase.h"
#include "MouseEventCase.h"
#include <vector>

struct ObjectFunc
{
	ObjectBase* object;

	ObjectFunc(ObjectBase* _object)
		: object(_object) {}
};