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
	if (!enabled) return;
	if (canvasId != -1) {
		SetDrawScreen(canvasId);
	}
	else {
		SetDrawScreen(DX_SCREEN_BACK);
	}
	if (enabledOutline) {
		int resultOuterColor = outerColor.Get();
		DrawLineAA(pos.x, pos.y, size.x, size.y, resultOuterColor, outlineWidth);
	}
	SetDrawScreen(DX_SCREEN_BACK);
}
