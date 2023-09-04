#include "ProgressObject.h"

void ProgressObject::SetupSlider()
{
	RegisterChildren(slider);
}

void ProgressObject::Collide()
{
	CollideMouseAsBox();
}

void ProgressObject::Update()
{
	UpdateEnforcedMouseCollision();

	// アニメーション記述をする場合，ここに記述
	if (mouseHit) {
		SetAnimationColorPoint(&innerAnimation, innerAnimation.current, hoveredInnerColor);
		SetAnimationColorPoint(&outerAnimation, outerAnimation.current, hoveredOuterColor);
		SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)hoveredInnerColor.a);
		SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)hoveredOuterColor.a);
	}
	else {
		SetAnimationColorPoint(&innerAnimation, innerAnimation.current, innerColor);
		SetAnimationColorPoint(&outerAnimation, outerAnimation.current, outerColor);
		SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)innerColor.a);
		SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)outerColor.a);
	}

	if (mouseSelected) {
		SetAnimationColorPoint(&innerAnimation, innerAnimation.current, selectedInnerColor);
		SetAnimationColorPoint(&outerAnimation, outerAnimation.current, selectedOuterColor);
		SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)selectedInnerColor.a);
		SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)selectedOuterColor.a);
	}

	if (mouseClicked) {
		SetAnimationColorPoint(&innerAnimation, innerAnimation.current, clickedInnerColor);
		SetAnimationColorPoint(&outerAnimation, outerAnimation.current, clickedOuterColor);
		SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)clickedInnerColor.a);
		SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)clickedOuterColor.a);
	}

	if (!enabled) {
		SetAnimationColorPoint(&innerAnimation, innerAnimation.current, disabledInnerColor);
		SetAnimationColorPoint(&outerAnimation, outerAnimation.current, disabledOuterColor);
		SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)disabledInnerColor.a);
		SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)disabledOuterColor.a);
	}

	if (mouseClicked && enabled) {
		PosVec mousePos = Input::MouseInput::GetMouse();
		float newRate;
		if (verticalMode) {
			newRate = (mousePos.y - pos.y) / size.y;
		}
		else {
			newRate = (mousePos.x - pos.x) / size.x;
		}
		if (newRate < 0.f) newRate = 0.f;
		else if (newRate > 1.f) newRate = 1.f;
		if (verticalMode) {
			slider->SetSize(PosVec(slider->GetSize().x, newRate * size.y));
		}
		else {
			slider->SetSize(PosVec(newRate * size.x, slider->GetSize().y));
		}
		value = newRate;
	}

	if (mouseSelected) {
		SetMouseOff();
	}

	UpdateAnimationColor(&innerAnimation);
	UpdateAnimationColor(&outerAnimation);
	UpdateAnimation(&innerAlphaAnimation);
	UpdateAnimation(&outerAlphaAnimation);

	slider->Update();

	UpdatePointerAnimation();
}

void ProgressObject::Draw()
{
	if (canvasId != -1) {
		SetDrawScreen(canvasId);
	}
	else {
		SetDrawScreen(DX_SCREEN_BACK);
	}
	SetDrawArea((int)pos.x, (int)pos.y, (int)(pos.x + size.x + 1), (int)(pos.y + size.y + 1));
	if (enabledFill) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)innerAlphaAnimation.current);
		int resultInnerColor = innerAnimation.current.Get();
		//DrawBoxAA(pos.x + outlineWidth, pos.y + outlineWidth, pos.x + size.x - outlineWidth + 1, pos.y + size.y - outlineWidth + 1, resultInnerColor, true, 0);
		DrawBoxAA(pos.x, pos.y, pos.x + size.x + 1, pos.y + size.y + 1, resultInnerColor, true, 0);
	}
	/*if (rectMode) eventRect.Draw();*/
	slider->Draw();
	if (canvasId != -1) {
		SetDrawScreen(canvasId);
	}
	else {
		SetDrawScreen(DX_SCREEN_BACK);
	}
	if (enabledOutline) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)outerAlphaAnimation.current);
		int resultOuterColor = outerAnimation.current.Get(); // debug
		//DrawBoxAA(pos.x, pos.y, pos.x + size.x, pos.y + size.y, resultOuterColor, true, 0);
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

void ProgressObject::CollideMouse()
{}
