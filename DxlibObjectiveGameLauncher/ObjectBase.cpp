#include "ObjectBase.h"


void ObjectBase::SetAnimationColorPoint(AnimationColorStatus& type, Color255 _start, Color255 _goal)
{
	type.elapsedTime = 0.f;

	type.start = _start;
	if (type.end.r != _goal.r &&
		type.end.g != _goal.g &&
		type.end.b != _goal.b) type.durationRemain = type.duration;
	type.end = _goal;

	if (type.durationRemain <= 0.f || !type.animationEnabled) {
		type.current = type.end;
		return;
	}

	type.m[0] = (type.end.r - type.start.r) / type.durationRemain;
	type.m[1] = (type.end.g - type.start.g) / type.durationRemain;
	type.m[2] = (type.end.b - type.start.b) / type.durationRemain;
}

void ObjectBase::UpdateAnimationColor(AnimationColorStatus& type)
{
	if (type.animationEnabled) {

		type.durationRemain -= ApplicationTime::DeltaTime();

		type.elapsedTime += ApplicationTime::DeltaTime();
		if (type.elapsedTime >= type.duration || type.durationRemain <= 0.f) {
			type.elapsedTime = type.duration;
			type.durationRemain = type.duration;
		}
		else {
			type.current = Color255(
				(int)(type.m[0] * type.elapsedTime + type.start.r),
				(int)(type.m[1] * type.elapsedTime + type.start.g),
				(int)(type.m[2] * type.elapsedTime + type.start.b));
		}
	}
}

void ObjectBase::SetAnimationPoint(AnimationStatus& type, float _start, float _goal)
{
	type.elapsedTime = 0.f;

	type.start = _start;
	if (type.end != _goal) {
		//printfDx("\n");
		type.durationRemain = type.duration;
	}
	type.end = _goal;

	if (type.durationRemain <= 0.f || !type.animationEnabled) {
		type.current = type.end;
		return;
	}
	type.m = (type.end - type.start) / type.durationRemain;
	
}

void ObjectBase::UpdateAnimation(AnimationStatus& type)
{
	if (type.animationEnabled) {

		type.durationRemain -= ApplicationTime::DeltaTime();

		type.elapsedTime += ApplicationTime::DeltaTime();
		if (type.elapsedTime >= type.duration || type.durationRemain <= 0.f) {
			type.elapsedTime = type.duration;
		}
		else {
			type.current += type.m * type.elapsedTime;
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