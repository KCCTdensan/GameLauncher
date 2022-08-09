#include "ObjectBase.h"


void ObjectBase::SetAnimationColorPoint(AnimationColorStatus* type, Color255 _start, Color255 _goal)
{
	type->elapsedTime = 0.f;

	type->start = _start;
	if (type->end.r != _goal.r &&
		type->end.g != _goal.g &&
		type->end.b != _goal.b) type->durationRemain = type->duration;
	type->end = _goal;
	type->current = _start;

	if (type->durationRemain <= 0.f || !type->animationEnabled) {
		type->current = type->end;
		return;
	}

	type->m[0] = (type->end.r - type->start.r) / type->durationRemain;
	type->m[1] = (type->end.g - type->start.g) / type->durationRemain;
	type->m[2] = (type->end.b - type->start.b) / type->durationRemain;
}

void ObjectBase::UpdateAnimationColor(AnimationColorStatus* type)
{
	if (type->animationEnabled) {

		type->durationRemain -= ApplicationTime::DeltaTime();

		type->elapsedTime += ApplicationTime::DeltaTime();
		if (type->elapsedTime >= type->duration || type->durationRemain <= 0.f) {
			type->elapsedTime = type->duration;
			type->durationRemain = type->duration;
		}
		else {
			type->current = Color255(
				(int)(type->m[0] * type->elapsedTime + type->start.r),
				(int)(type->m[1] * type->elapsedTime + type->start.g),
				(int)(type->m[2] * type->elapsedTime + type->start.b));
		}
	}
}

void ObjectBase::SetAnimationPoint(AnimationStatus* type, float _start, float _goal)
{
	type->elapsedTime = 0.f;

	type->start = _start;
	if (type->end != _goal) {
		//printfDx("\n");
		type->durationRemain = type->duration;
	}
	type->end = _goal;

	if (type->durationRemain <= 0.f || !type->animationEnabled) {
		type->current = type->end;
		return;
	}
	type->m = (type->end - type->start) / type->durationRemain;
	
}

void ObjectBase::UpdateAnimation(AnimationStatus* type)
{
	if (type->animationEnabled) {

		type->durationRemain -= ApplicationTime::DeltaTime();

		type->elapsedTime += ApplicationTime::DeltaTime();
		if (type->elapsedTime >= type->duration || type->durationRemain <= 0.f) {
			type->elapsedTime = type->duration;
		}
		else {
			type->current += type->m * type->elapsedTime;
		}
	}
}

void ObjectBase::UpdatePointerAnimation()
{
	for (auto it = pAnimation.begin(); it != pAnimation.end(); it++) {
		UpdateAnimationColor(&(it->animation));
		*it->color = it->animation.current;
		if (it->animation.durationRemain <= 0.f) {
			pAnimation.erase(it);
			break;
		}
	}
}

void ObjectBase::ChangeColorWithAnimation(Color255* pColor, Color255* endColor, float duration)
{
	for (auto it = pAnimation.begin(); it != pAnimation.end(); it++) {
		if (it->color == pColor) {
			if (it->animation.end.r == endColor->r &&
				it->animation.end.g == endColor->g &&
				it->animation.end.b == endColor->b) return;
			else {
				pAnimation.erase(it);
				break;
			}
		}
	}

	AnimationColorPointer* p = new AnimationColorPointer(
		AnimationColorStatus(),
		pColor
	);
	p->animation.animationEnabled = true;
	p->animation.duration = duration;
	p->animation.durationRemain = duration;
	p->animation.elapsedTime = 0.f;
	SetAnimationColorPoint(&(p->animation), *pColor, *endColor);
	pAnimation.push_back(*p);
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