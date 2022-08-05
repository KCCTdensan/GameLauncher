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
		SetAnimationPoint(currentInnerColor, hoveredColor);
	}
	else {
		SetAnimationPoint(currentInnerColor, innerColor);
	}

	if (mouseSelected) {
		SetAnimationPoint(currentInnerColor, selectedColor);
	}

	if (mouseClicked) {
		SetAnimationPoint(currentInnerColor, clickedColor);
	}

	if (animationEnabled) {

		animationDuraionRemain -= ApplicationTime::DeltaTime();

		animationElapsedTime += ApplicationTime::DeltaTime();
		if (animationElapsedTime >= animationDuraion || animationDuraionRemain <= 0.f) {
			animationElapsedTime = animationDuraion;
			animationDuraionRemain = animationDuraion;
		}
		else {
			currentInnerColor = Color255(
				(int)(mRed * animationElapsedTime + animationStartColor.r),
				(int)(mGreen * animationElapsedTime + animationStartColor.g),
				(int)(mBlue * animationElapsedTime + animationStartColor.b));
		}
	}

	if (!enabled) return;

}

void ButtonObject::Draw()
{
	if (!enabled) return;

	if (enabledOutline) {
		int resultOuterColor = outerColor.Get(); // debug
		DrawBoxAA(pos.x, pos.y, pos.x + size.x, pos.y + size.y, resultOuterColor, true, 0);
	}
	if (enabledFill) {
		int resultInnerColor = currentInnerColor.Get();
		DrawBoxAA(pos.x + outlineWidth, pos.y + outlineWidth, pos.x + size.x - outlineWidth, pos.y + size.y - outlineWidth, resultInnerColor, true, 0);
	}
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

void ButtonObject::SetAnimationPoint(Color255 _start, Color255 _goal)
{
	animationElapsedTime = 0.f;

	animationStartColor = _start;
	if (animationEndColor.r != _goal.r &&
		animationEndColor.g != _goal.g &&
		animationEndColor.b != _goal.b) animationDuraionRemain = animationDuraion;
	animationEndColor = _goal;

	if (animationDuraionRemain <= 0.f || !animationEnabled) {
		currentInnerColor = animationEndColor;
		return;
	}

	mRed = (animationEndColor.r - animationStartColor.r) / animationDuraionRemain;
	mGreen = (animationEndColor.g - animationStartColor.g) / animationDuraionRemain;
	mBlue = (animationEndColor.b - animationStartColor.b) / animationDuraionRemain;
}
