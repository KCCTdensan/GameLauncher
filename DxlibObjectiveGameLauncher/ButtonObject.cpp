#include "ButtonObject.h"

void ButtonObject::Update()
{
	// �A�j���[�V�����L�q������ꍇ�C�����ɋL�q
	CollideMouse();

	if (mouseHit) {
		currentInnerColor = hoveredColor;
	}
	else {
		currentInnerColor = innerColor;
	}

	if (!enabled) return;

}

void ButtonObject::Draw()
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

void ButtonObject::CollideMouse()
{
	if (pos.x <= Input::MouseInput::GetMouse().x &&
		pos.x + size.x >= Input::MouseInput::GetMouse().x &&
		pos.y <= Input::MouseInput::GetMouse().y &&
		pos.y + size.y >= Input::MouseInput::GetMouse().y) {

		mouseHit = true;
	}
	else {
		mouseHit = false;
	}
}
