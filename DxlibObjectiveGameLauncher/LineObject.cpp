#include "LineObject.h"

void LineObject::Collide()
{
	UpdatePointerAnimation();
}

void LineObject::Update()
{
}

void LineObject::Draw()
{
	if (enabledOutline) {
		int resultOuterColor = outerColor.Get();
		DrawLineAA(pos.x, pos.y, size.x, size.y, resultOuterColor, outlineWidth);
	}
}
