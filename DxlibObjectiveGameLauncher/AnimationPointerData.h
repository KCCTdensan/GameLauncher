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