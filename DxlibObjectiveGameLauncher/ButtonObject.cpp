#include "ButtonObject.h"

void ButtonObject::Collide()
{
	CollideMouse();
}

void ButtonObject::Update()
{
	CheckGUID();

	// アニメーション記述をする場合，ここに記述
	if (mouseHit) {
		SetAnimationColorPoint(innerAnimation, innerAnimation.current, hoveredInnerColor);
		SetAnimationColorPoint(outerAnimation, outerAnimation.current, hoveredOuterColor);
		SetAnimationPoint(innerAlphaAnimation, innerAnimation.current.a, hoveredInnerColor.a);
		SetAnimationPoint(outerAlphaAnimation, outerAnimation.current.a, hoveredOuterColor.a);
	}
	else {
		SetAnimationColorPoint(innerAnimation, innerAnimation.current, innerColor);
		SetAnimationColorPoint(outerAnimation, outerAnimation.current, outerColor);
		SetAnimationPoint(innerAlphaAnimation, innerAnimation.current.a, innerColor.a);
		SetAnimationPoint(outerAlphaAnimation, outerAnimation.current.a, outerColor.a);
	}

	if (mouseSelected) {
		SetAnimationColorPoint(innerAnimation, innerAnimation.current, selectedInnerColor);
		SetAnimationColorPoint(outerAnimation, outerAnimation.current, selectedOuterColor);
		SetAnimationPoint(innerAlphaAnimation, innerAnimation.current.a, selectedInnerColor.a);
		SetAnimationPoint(outerAlphaAnimation, outerAnimation.current.a, selectedOuterColor.a);
	}

	if (mouseClicked) {
		SetAnimationColorPoint(innerAnimation, innerAnimation.current, clickedInnerColor);
		SetAnimationColorPoint(outerAnimation, outerAnimation.current, clickedOuterColor);
		SetAnimationPoint(innerAlphaAnimation, innerAnimation.current.a, clickedInnerColor.a);
		SetAnimationPoint(outerAlphaAnimation, outerAnimation.current.a, clickedOuterColor.a);
	}

	UpdateAnimationColor(innerAnimation);
	UpdateAnimationColor(outerAnimation);
	UpdateAnimation(innerAlphaAnimation);
	UpdateAnimation(outerAlphaAnimation);

	if (!enabled) return;

}

void ButtonObject::Draw()
{
	if (!enabled) return;

	if (enabledOutline) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, outerAlphaAnimation.current);
		int resultOuterColor = outerAnimation.current.Get(); // debug
		DrawBoxAA(pos.x, pos.y, pos.x + size.x, pos.y + size.y, resultOuterColor, true, 0);
	}
	if (enabledFill) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, innerAlphaAnimation.current);
		int resultInnerColor = innerAnimation.current.Get();
		DrawBoxAA(pos.x + outlineWidth, pos.y + outlineWidth, pos.x + size.x - outlineWidth, pos.y + size.y - outlineWidth, resultInnerColor, true, 0);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ButtonObject::CollideMouse()
{

	bool beforeMouseClicked = mouseClicked;
	bool goSelecting = false;

	if (pos.x <= Input::MouseInput::GetMouse().x &&
		pos.x + size.x >= Input::MouseInput::GetMouse().x &&
		pos.y <= Input::MouseInput::GetMouse().y &&
		pos.y + size.y >= Input::MouseInput::GetMouse().y) {

		mouseHit = true;

		// オブジェクトの重複判定登録処理
		ObjectOverlapping::UpdateObject(guid);

		if (Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) >= PressFrame::FIRST) {
			if (Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) == PressFrame::FIRST /*&& !beCalledNoMouse*/)
				mouseClicked = true;

			// 重複中の別オブジェ対策
			//if (ObjectOverlapping<ButtonObject>::GetObj() != this) mouseSelected = false;
		}
		else {
			mouseClicked = false;
			goSelecting = true;
		}
	}
	else {
		mouseHit = false;

		if (Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) >= PressFrame::FIRST && !mouseClicked) {
			mouseSelected = false;
		}
	}

	if (Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) == PressFrame::ZERO)
		mouseClicked = false;

	if (beforeMouseClicked && !mouseClicked && goSelecting) {
		mouseSelected = true;
	}

	beCalledNoMouse = false;
}

void ButtonObject::SetInnerAlphaAnimationPoint(int _start, int _goal)
{
}

void ButtonObject::SetOuterAlphaAnimationPoint(int _start, int _goal)
{
}

void ButtonObject::UpdateInnerAlphaColor()
{
}

void ButtonObject::UpdateOuterAlphaColor()
{
}
