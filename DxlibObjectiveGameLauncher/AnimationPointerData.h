#pragma once
#include "AnimationStatus.h"

struct AnimationColorPointer {
	AnimationColorStatus animation;
	Color255* color;

	AnimationColorPointer()
		: animation(), color(nullptr) {}

	AnimationColorPointer(AnimationColorStatus _status, Color255* _color)
		:animation(_status), color(_color) {}
};

struct AnimationPointer {
	AnimationStatus animation;
	float* value;

	AnimationPointer()
		: animation(), value(nullptr) {}

	AnimationPointer(AnimationStatus _status, float* _value)
		:animation(_status), value(_value) {}
};