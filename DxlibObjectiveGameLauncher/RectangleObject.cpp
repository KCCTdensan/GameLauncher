#include "RectangleObject.h"

void RectangleObject::Collide()
{
	CollideMouse();
}

void RectangleObject::Update()
{
	CheckGUID();

	currentInnerColor = innerColor;
	UpdatePointerAnimation();
}

void RectangleObject::Draw()
{
	if (!enabled) return;
	SetDrawArea((int)pos.x, (int)pos.y, (int)(pos.x + size.x + 1), (int)(pos.y + size.y + 1));
	if (enabledOutline) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)outerAlphaAnimation.current);
		int resultOuterColor = outerColor.Get(); // debug
		DrawBoxAA(pos.x, pos.y, pos.x + size.x, pos.y + size.y, resultOuterColor, true, 0);
	}
	if (enabledFill) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)innerAlphaAnimation.current);
		int resultInnerColor = currentInnerColor.Get();
		DrawBoxAA(pos.x + outlineWidth, pos.y + outlineWidth, pos.x + size.x - outlineWidth, pos.y + size.y - outlineWidth, resultInnerColor, true, 0);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawArea(0, 0, (int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y);
}

void RectangleObject::CollideMouse()
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
			if (Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) == PressFrame::FIRST /*&& !beCalledNoMouse*/) {
				mouseClicked = true;
			}

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
