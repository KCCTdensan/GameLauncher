#include "ImageObject.h"

void ImageObject::Collide()
{
	CollideMouseAsBox(); // àÍâûèàóùÇµÇ‹Ç∑ÅBâÊëúîªíËÇ∆ÇµÇƒ
}

void ImageObject::Update()
{
	CheckGUID();
	UpdateEnforcedMouseCollision();

	SetAnimationColorPoint(&innerAnimation, innerAnimation.current, innerColor);
	SetAnimationColorPoint(&outerAnimation, outerAnimation.current, outerColor);
	SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)innerColor.a);
	SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)outerColor.a);
	SetAnimationPoint(&imageAlphaAnimation, (float)imageAlphaAnimation.current, (float)defaultImageColor.a);

	UpdateAnimationColor(&innerAnimation);
	UpdateAnimationColor(&outerAnimation);
	UpdateAnimation(&innerAlphaAnimation);
	UpdateAnimation(&outerAlphaAnimation);
	UpdateAnimation(&imageAlphaAnimation); // âÊëúalphaíl

	UpdatePointerAnimation();
}

void ImageObject::Draw()
{
	if (canvasId != -1) {
		SetDrawScreen(canvasId);
	}
	else {
		SetDrawScreen(DX_SCREEN_BACK);
	}
	SetDrawArea((int)pos.x, (int)pos.y, (int)(pos.x + size.x + 1), (int)(pos.y + size.y + 1));
	if (enabledFill) { // âÊëúÇÃâ∫ÇÃï`âÊ
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)innerAlphaAnimation.current);
		int resultInnerColor = innerAnimation.current.Get();
		DrawBoxAA(pos.x, pos.y, pos.x + size.x + 1, pos.y + size.y + 1, resultInnerColor, true, 0);
	}

	// ñ{ï`âÊ
	DrawImage();

	if (canvasId != -1) {
		SetDrawScreen(canvasId);
	}
	else {
		SetDrawScreen(DX_SCREEN_BACK);
	}
	if (enabledOutline) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)outerAlphaAnimation.current);
		int resultOuterColor = outerAnimation.current.Get(); // debug
		float offset = outlineWidth / 2;
		DrawLineAA(pos.x + offset, pos.y + offset, pos.x + size.x - offset + 1, pos.y + offset, resultOuterColor, outlineWidth);
		DrawLineAA(pos.x + size.x - offset, pos.y + offset, pos.x + size.x - offset, pos.y + size.y - offset + 1, resultOuterColor, outlineWidth);
		DrawLineAA(pos.x + size.x - offset, pos.y + size.y - offset, pos.x + offset - 1, pos.y + size.y - offset, resultOuterColor, outlineWidth);
		DrawLineAA(pos.x + offset, pos.y + size.y - offset, pos.x + offset, pos.y + offset - 1, resultOuterColor, outlineWidth);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	SetDrawArea(0, 0, (int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y);

	SetDrawScreen(DX_SCREEN_BACK);
}
