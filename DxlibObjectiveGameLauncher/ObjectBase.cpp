#include "ObjectBase.h"


void ObjectBase::SetAnimationPoint(Color255 _start, Color255 _goal)
{
	animationElapsedTime = 0.f;

	animationStartColor = _start;
	if (animationEndColor.r != _goal.r &&
		animationEndColor.g != _goal.g &&
		animationEndColor.b != _goal.b) animationDuraionRemain = animationDuraion;
	animationEndColor = _goal;

	if (animationDuraionRemain <= 0.f || !animationEnabled) {
		currentInnerColor = animationEndColor;
		return;
	}

	mRed = (animationEndColor.r - animationStartColor.r) / animationDuraionRemain;
	mGreen = (animationEndColor.g - animationStartColor.g) / animationDuraionRemain;
	mBlue = (animationEndColor.b - animationStartColor.b) / animationDuraionRemain;
}

bool ObjectBase::Move(PosVec _delta)
{
	pos = PosVec(pos.x + _delta.x, pos.y + _delta.y);

	// 子要素にも適用
	for (int i = 0; i < children.size(); i++) {
		children[i]->Move(_delta);
	}
	return true;
}