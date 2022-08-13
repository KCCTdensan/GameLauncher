#include "CanvasObject.h"

void CanvasObject::Collide()
{
	CollideMouse();

	for (auto& item : scrollButton) {
		item.Collide();
	}
}

void CanvasObject::Update()
{
	CheckGUID();
	SetAnimationColorPoint(&innerAnimation, innerAnimation.current, innerColor);
	SetAnimationColorPoint(&outerAnimation, outerAnimation.current, outerColor);
	SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)innerColor.a);
	SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)outerColor.a);

	UpdateAnimationColor(&innerAnimation);
	UpdateAnimationColor(&outerAnimation);
	UpdateAnimation(&innerAlphaAnimation);
	UpdateAnimation(&outerAlphaAnimation);
	
	for (auto& item : scrollButton) {
		item.Update();
	}

	float distance = 0.3f;

	if (scrollButton[(int)DirectionType::LEFT].GetMouseSelected()) {
		distance *= -1.f;
		if (scrollValue.x + distance < 0.001f) {
			distance = -scrollValue.x;
		}
		scrollValue.x += distance;
		Move(PosVec(distance * (scrollDistance.x - size.x), 0.f), false);
		for (auto& item : scrollButton) {
			item.Move(PosVec(-distance * (scrollDistance.x - size.x), 0.f));
		}
		scrollButton[(int)DirectionType::LEFT].SetMouseOff();
	}

	if (scrollButton[(int)DirectionType::RIGHT].GetMouseSelected()) {
		if (scrollValue.x + distance > 1.001f) {
			distance = 1.f - scrollValue.x;
		}
		scrollValue.x += distance;
		Move(PosVec(distance * (scrollDistance.x - size.x), 0.f), false);
		for (auto& item : scrollButton) {
			item.Move(PosVec(-distance * (scrollDistance.x - size.x), 0.f));
		}
		scrollButton[(int)DirectionType::RIGHT].SetMouseOff();
	}

	if (scrollButton[(int)DirectionType::TOP].GetMouseSelected()) {
		distance *= -1.f;
		if (scrollValue.y + distance < 0.001f) {
			distance = -scrollValue.y;
		}
		scrollValue.y += distance;
		Move(PosVec(0.f, distance * (scrollDistance.y - size.y)), false);
		for (auto& item : scrollButton) {
			item.Move(PosVec(0.f, -distance * (scrollDistance.y - size.y), 0.f));
		}
		scrollButton[(int)DirectionType::TOP].SetMouseOff();
	}

	if (scrollButton[(int)DirectionType::BOTTOM].GetMouseSelected()) {
		if (scrollValue.y + distance > 1.001f) {
			distance = 1.f - scrollValue.y;
		}
		scrollValue.y += distance;
		Move(PosVec(0.f, distance * (scrollDistance.y - size.y)), false);
		for (auto& item : scrollButton) {
			item.Move(PosVec(0.f, -distance * (scrollDistance.y - size.y), 0.f));
		}
		scrollButton[(int)DirectionType::BOTTOM].SetMouseOff();
	}

	UpdatePointerAnimation();
	if (scrollValue.x > 1.f) scrollValue.x = 1.f;
	if (scrollValue.y > 1.f) scrollValue.y = 1.f;
	if (scrollValue.x < 0.f) scrollValue.x = 0.f;
	if (scrollValue.y < 0.f) scrollValue.y = 0.f;
	maskUpperLeft.x = (scrollDistance.x - size.x) * scrollValue.x;
	maskUpperLeft.y = (scrollDistance.y - size.y) * scrollValue.y;

	// Canvasリセット
	SetDrawScreen(canvasId);
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)innerAlphaAnimation.current);
	DrawBoxAA(0.f, 0.f, scrollDistance.x, scrollDistance.y, innerAnimation.current.Get(), true, 0.f);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawScreen(DX_SCREEN_BACK);

}

void CanvasObject::Draw()
{
	if (!enabled) return;
	//SetDrawArea((int)pos.x, (int)pos.y, (int)(pos.x + size.x + 1), (int)(pos.y + size.y + 1));
	//if (enabledFill) {
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)innerAlphaAnimation.current);
	//	int resultInnerColor = innerAnimation.current.Get();
	//	DrawBoxAA(pos.x + outlineWidth, pos.y + outlineWidth, pos.x + size.x - outlineWidth, pos.y + size.y - outlineWidth, resultInnerColor, true, 0);
	//}
	//if (enabledOutline) {
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)outerAlphaAnimation.current);
	//	int resultOuterColor = outerAnimation.current.Get(); // debug
	//	//DrawBoxAA(pos.x, pos.y, pos.x + size.x, pos.y + size.y, resultOuterColor, true, 0);
	//	float offset = outlineWidth / 2;
	//	DrawLineAA(pos.x + offset, pos.y + offset, pos.x + size.x - offset + 1, pos.y + offset, resultOuterColor, outlineWidth);
	//	DrawLineAA(pos.x + size.x - offset, pos.y + offset, pos.x + size.x - offset, pos.y + size.y - offset + 1, resultOuterColor, outlineWidth);
	//	DrawLineAA(pos.x + size.x - offset, pos.y + size.y - offset, pos.x + offset - 1, pos.y + size.y - offset, resultOuterColor, outlineWidth);
	//	DrawLineAA(pos.x + offset, pos.y + size.y - offset, pos.x + offset, pos.y + offset - 1, resultOuterColor, outlineWidth);
	//}
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//SetDrawArea(0, 0, (int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y);

	// canvasDrawingId = DerivationGraphF(maskUpperLeft.x, maskUpperLeft.y, size.x, size.y, canvasId);
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRectGraphF(pos.x, pos.y, (int)pos.x, (int)pos.y, (int)size.x, (int)size.y, canvasId, true, false);

	for (auto& item : scrollButton) {
		item.Draw();
	}
	
	/*DrawModiGraphF(
		0.f, 0.f,
		0.f + size.x, 0.f,
		0.f + size.x, 0.f + size.y,
		0.f, 0.f + size.y,
		canvasDrawingId, true);
	DeleteGraph(canvasDrawingId);*/
}

bool CanvasObject::RegisterChildren(ObjectBase* _object)
{
	ObjectBase::RegisterChildren(_object);
	_object->SetCanvasId(canvasId);
	_object->RegisterParent(this);
	// キャンバス追加
	return true;
}

void CanvasObject::CollideMouse()
{
	if (!enabled) return;

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
