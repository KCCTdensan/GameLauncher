#include "ObjectBase.h"


void ObjectBase::SetInnerAnimationPoint(Color255 _start, Color255 _goal)
{
	animationInnerElapsedTime = 0.f;

	animationStartInnerColor = _start;
	if (animationEndInnerColor.r != _goal.r &&
		animationEndInnerColor.g != _goal.g &&
		animationEndInnerColor.b != _goal.b) animationInnerDuraionRemain = animationInnerDuration;
	animationEndInnerColor = _goal;

	if (animationInnerDuraionRemain <= 0.f || !animationInnerEnabled) {
		currentInnerColor = animationEndInnerColor;
		return;
	}

	mInnerRed = (animationEndInnerColor.r - animationStartInnerColor.r) / animationInnerDuraionRemain;
	mInnerGreen = (animationEndInnerColor.g - animationStartInnerColor.g) / animationInnerDuraionRemain;
	mInnerBlue = (animationEndInnerColor.b - animationStartInnerColor.b) / animationInnerDuraionRemain;
}

void ObjectBase::SetOuterAnimationPoint(Color255 _start, Color255 _goal)
{
	animationOuterElapsedTime = 0.f;

	animationStartOuterColor = _start;
	if (animationEndOuterColor.r != _goal.r &&
		animationEndOuterColor.g != _goal.g &&
		animationEndOuterColor.b != _goal.b) animationOuterDuraionRemain = animationOuterDuration;
	animationEndOuterColor = _goal;

	if (animationOuterDuraionRemain <= 0.f || !animationOuterEnabled) {
		currentOuterColor = animationEndOuterColor;
		return;
	}

	mOuterRed = (animationEndOuterColor.r - animationStartOuterColor.r) / animationOuterDuraionRemain;
	mOuterGreen = (animationEndOuterColor.g - animationStartOuterColor.g) / animationOuterDuraionRemain;
	mOuterBlue = (animationEndOuterColor.b - animationStartOuterColor.b) / animationOuterDuraionRemain;
}

void ObjectBase::UpdateInnerColor()
{
	if (animationInnerEnabled) {

		animationInnerDuraionRemain -= ApplicationTime::DeltaTime();

		animationInnerElapsedTime += ApplicationTime::DeltaTime();
		if (animationInnerElapsedTime >= animationInnerDuration || animationInnerDuraionRemain <= 0.f) {
			animationInnerElapsedTime = animationInnerDuration;
			animationInnerDuraionRemain = animationInnerDuration;
		}
		else {
			currentInnerColor = Color255(
				(int)(mInnerRed * animationInnerElapsedTime + animationStartInnerColor.r),
				(int)(mInnerGreen * animationInnerElapsedTime + animationStartInnerColor.g),
				(int)(mInnerBlue * animationInnerElapsedTime + animationStartInnerColor.b));
		}
	}
}

void ObjectBase::UpdateOuterColor()
{
	if (animationOuterEnabled) {

		animationOuterDuraionRemain -= ApplicationTime::DeltaTime();

		animationOuterElapsedTime += ApplicationTime::DeltaTime();
		if (animationOuterElapsedTime >= animationOuterDuration || animationOuterDuraionRemain <= 0.f) {
			animationOuterElapsedTime = animationOuterDuration;
			animationOuterDuraionRemain = animationOuterDuration;
		}
		else {
			currentOuterColor = Color255(
				(int)(mOuterRed * animationOuterElapsedTime + animationStartOuterColor.r),
				(int)(mOuterGreen * animationOuterElapsedTime + animationStartOuterColor.g),
				(int)(mOuterBlue * animationOuterElapsedTime + animationStartOuterColor.b));
		}
	}
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