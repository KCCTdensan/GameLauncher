#include "LineObject.h"

void LineObject::Collide()
{
}

void LineObject::Update()
{
	UpdatePointerAnimation();
}

void LineObject::Draw()
{
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
