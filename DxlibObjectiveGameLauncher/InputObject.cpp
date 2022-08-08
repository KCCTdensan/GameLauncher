#include "InputObject.h"

void InputObject::Collide()
{
	CollideMouse();
	textObject.Collide();
}

void InputObject::Update()
{
	CheckGUID();

	// アニメーション記述をする場合，ここに記述
	if (mouseHit) {
		SetAnimationColorPoint(innerAnimation, innerAnimation.current, hoveredInnerColor);
		SetAnimationColorPoint(outerAnimation, outerAnimation.current, hoveredOuterColor);
		SetAnimationPoint(innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)hoveredInnerColor.a);
		SetAnimationPoint(outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)hoveredOuterColor.a);
	}
	else {
		SetAnimationColorPoint(innerAnimation, innerAnimation.current, innerColor);
		SetAnimationColorPoint(outerAnimation, outerAnimation.current, outerColor);
		SetAnimationPoint(innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)innerColor.a);
		SetAnimationPoint(outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)outerColor.a);
	}

	if (mouseSelected) {
		SetAnimationColorPoint(innerAnimation, innerAnimation.current, selectedInnerColor);
		SetAnimationColorPoint(outerAnimation, outerAnimation.current, selectedOuterColor);
		SetAnimationPoint(innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)selectedInnerColor.a);
		SetAnimationPoint(outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)selectedOuterColor.a);
		
		if (!interruptMode) {
			// アクティブ
			if (GetActiveKeyInput() != inputHandle && !turnedOn) {
				SetActiveKeyInput(inputHandle);
				turnedOn = true;
			}

			char text[256] = "";
			GetKeyInputString(text, inputHandle);
			inputText = text;
			textObject.SetText(inputText);
		}
		else {
			char text[256] = "";
			textObject.SetText("");
			Draw();
			KeyInputString((int)pos.x, (int)pos.y, 256, text, true);
			inputText = text;
			textObject.SetText(inputText);
			SetMouseOff();
		}
		textObject.Update();
	}
	else {
		if (GetActiveKeyInput() == inputHandle && turnedOn) {
			SetActiveKeyInput(-1);
			SetMouseOff();
			turnedOn = false;
		}
	}

	if (mouseClicked) {
		SetAnimationColorPoint(innerAnimation, innerAnimation.current, clickedInnerColor);
		SetAnimationColorPoint(outerAnimation, outerAnimation.current, clickedOuterColor);
		SetAnimationPoint(innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)clickedInnerColor.a);
		SetAnimationPoint(outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)clickedOuterColor.a);
	}

	UpdateAnimationColor(innerAnimation);
	UpdateAnimationColor(outerAnimation);
	UpdateAnimation(innerAlphaAnimation);
	UpdateAnimation(outerAlphaAnimation);

	if (GetActiveKeyInput() != inputHandle && turnedOn) {
		if (CheckKeyInput(inputHandle) != 0) {
			SetActiveKeyInput(-1);
			SetMouseOff();
			turnedOn = false;
		}
	}

	if (!enabled) return;
}

void InputObject::Draw()
{
	if (!enabled) return;

	if (enabledOutline) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)outerAlphaAnimation.current);
		int resultOuterColor = outerAnimation.current.Get(); // debug
		//DrawBoxAA(pos.x, pos.y, pos.x + size.x, pos.y + size.y, resultOuterColor, true, 0);
		float offset = outlineWidth / 2;
		DrawLineAA(pos.x + offset, pos.y + offset, pos.x + size.x - offset + 1, pos.y + offset, resultOuterColor, outlineWidth);
		DrawLineAA(pos.x + size.x - offset, pos.y + offset, pos.x + size.x - offset, pos.y + size.y - offset + 1, resultOuterColor, outlineWidth);
		DrawLineAA(pos.x + size.x - offset + 1, pos.y + size.y - offset, pos.x + offset - 1, pos.y + size.y - offset, resultOuterColor, outlineWidth);
		DrawLineAA(pos.x + offset, pos.y + size.y - offset, pos.x + offset, pos.y + offset - 1, resultOuterColor, outlineWidth);
	}
	if (enabledFill) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)innerAlphaAnimation.current);
		int resultInnerColor = innerAnimation.current.Get();
		DrawBoxAA(pos.x + outlineWidth, pos.y + outlineWidth, pos.x + size.x - outlineWidth + 1, pos.y + size.y - outlineWidth + 1, resultInnerColor, true, 0);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	textObject.Draw();
}

void InputObject::CollideMouse()
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
