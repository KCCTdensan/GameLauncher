#include "RectangleObject.h"

void RectangleObject::Update()
{
	currentInnerColor = innerColor;
}

void RectangleObject::Draw()
{
	if (!enabled) return;

	if (enabledOutline) {
		int resultOuterColor = outerColor; // debug
		DrawBoxAA(pos.x, pos.y, pos.x + size.x, pos.y + size.y, resultOuterColor, true, 0);
	}
	if (enabledFill) {
		int resultInnerColor = currentInnerColor;
		DrawBoxAA(pos.x + outlineWidth, pos.y + outlineWidth, pos.x + size.x - outlineWidth, pos.y + size.y - outlineWidth, resultInnerColor, true, 0);
	}
}
