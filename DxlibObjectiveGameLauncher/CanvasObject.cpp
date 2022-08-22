#include "CanvasObject.h"

void CanvasObject::Collide()
{
	CollideMouse();

	for (auto& item : scrollBar) {
		item.Collide();
	}

	for (auto& item : scrollButton) {
		item.Collide();
	}
}

void CanvasObject::Update()
{
	SetAnimationColorPoint(&innerAnimation, innerAnimation.current, innerColor);
	SetAnimationColorPoint(&outerAnimation, outerAnimation.current, outerColor);
	SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)innerColor.a);
	SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)outerColor.a);

	UpdateAnimationColor(&innerAnimation);
	UpdateAnimationColor(&outerAnimation);
	UpdateAnimation(&innerAlphaAnimation);
	UpdateAnimation(&outerAlphaAnimation);

	for (auto& item : scrollBar) {
		item.Update();
	}

	if (scrollValue.y != scrollBar[0].GetValue() && enabled) {
		float distance = scrollBar[0].GetValue() - scrollValue.y;
		if (scrollValue.y + distance > 1.001f) {
			distance = 1.f - scrollValue.y;
		}
		else if (scrollValue.y + distance < 0.001f) {
			distance = -scrollValue.y;
		}
		scrollValue.y += distance;
		Move(PosVec(0.f, -distance * (scrollDistance.y - size.y)), false);
		for (auto& item : scrollButton) {
			item.Move(PosVec(0.f, distance * (scrollDistance.y - size.y), 0.f));
		}
		for (auto& item : scrollBar) {
			item.Move(PosVec(0.f, distance * (scrollDistance.y - size.y), 0.f));
		}
		scrollValue.y = scrollBar[0].GetValue();
	}

	if (scrollValue.x != scrollBar[1].GetValue() && enabled) {
		float distance = scrollBar[1].GetValue() - scrollValue.x;
		if (scrollValue.x + distance > 1.001f) {
			distance = 1.f - scrollValue.x;
		}
		else if (scrollValue.x + distance < 0.001f) {
			distance = -scrollValue.x;
		}
		scrollValue.x += distance;
		Move(PosVec(-distance * (scrollDistance.x - size.x), 0.f), false);
		for (auto& item : scrollButton) {
			item.Move(PosVec(distance * (scrollDistance.x - size.x), 0.f));
		}
		for (auto& item : scrollBar) {
			item.Move(PosVec(distance * (scrollDistance.x - size.x), 0.f));
		}
		scrollValue.x = scrollBar[1].GetValue();
	}

	for (auto& item : scrollButton) {
		item.Update();
	}

	float distance = scrollPercentage;

	if (scrollButton[(int)DirectionType::LEFT].GetMouseSelected() || (mouseHit && !scrollVertical && Input::MouseInput::GetWheelRot() > 0.f) && enabled && ObjectOverlapping::GetGUIDForCanvas() == guid) {
		distance *= -1.f;
		if (scrollValue.x + distance < 0.001f) {
			distance = -scrollValue.x;
		}
		scrollValue.x += distance;
		Move(PosVec(-distance * (scrollDistance.x - size.x), 0.f), false);
		if (parent != nullptr) {
			if (parent->GetCanvasOwner())
				parent->Move(PosVec(distance * (scrollDistance.x - size.x), 0.f));
		}
		for (auto& item : scrollButton) {
			item.Move(PosVec(distance * (scrollDistance.x - size.x), 0.f));
		}
		for (auto& item : scrollBar) {
			item.Move(PosVec(distance * (scrollDistance.x - size.x), 0.f));
		}
		scrollButton[(int)DirectionType::LEFT].SetMouseOff();
		scrollBar[1].SetValue(scrollValue.x);

		if (scrollValue.x <= 0.f) scrollButton[(int)DirectionType::LEFT].SetEnabled(false);
		scrollButton[(int)DirectionType::RIGHT].SetEnabled(true);
	}

	if (scrollButton[(int)DirectionType::RIGHT].GetMouseSelected() || (mouseHit && !scrollVertical && Input::MouseInput::GetWheelRot() < 0.f) && enabled && ObjectOverlapping::GetGUIDForCanvas() == guid) {
		if (scrollValue.x + distance > 1.001f) {
			distance = 1.f - scrollValue.x;
		}
		scrollValue.x += distance;
		Move(PosVec(-distance * (scrollDistance.x - size.x), 0.f), false);
		if (parent != nullptr) {
			if (parent->GetCanvasOwner())
				parent->Move(PosVec(distance * (scrollDistance.x - size.x), 0.f));
		}
		for (auto& item : scrollButton) {
			item.Move(PosVec(distance * (scrollDistance.x - size.x), 0.f));
		}
		for (auto& item : scrollBar) {
			item.Move(PosVec(distance * (scrollDistance.x - size.x), 0.f));
		}
		scrollButton[(int)DirectionType::RIGHT].SetMouseOff();
		scrollBar[1].SetValue(scrollValue.x);

		if (scrollValue.x >= 0.9999f) scrollButton[(int)DirectionType::RIGHT].SetEnabled(false);
		scrollButton[(int)DirectionType::LEFT].SetEnabled(true);
	}

	if (scrollButton[(int)DirectionType::TOP].GetMouseSelected() || (mouseHit && scrollVertical && Input::MouseInput::GetWheelRot() > 0.f) && enabled && ObjectOverlapping::GetGUIDForCanvas() == guid) {
		distance *= -1.f;
		if (scrollValue.y + distance < 0.001f) {
			distance = -scrollValue.y;
		}
		scrollValue.y += distance;
		Move(PosVec(0.f, -distance * (scrollDistance.y - size.y)), false);
		if (parent != nullptr) {
			if (parent->GetCanvasOwner())
				parent->Move(PosVec(0.f, distance * (scrollDistance.y - size.y), 0.f));
		}
		for (auto& item : scrollButton) {
			item.Move(PosVec(0.f, distance * (scrollDistance.y - size.y), 0.f));
		}
		for (auto& item : scrollBar) {
			item.Move(PosVec(0.f, distance * (scrollDistance.y - size.y), 0.f));
		}
		scrollButton[(int)DirectionType::TOP].SetMouseOff();
		scrollBar[0].SetValue(scrollValue.y);

		if (scrollValue.y <= 0.f) scrollButton[(int)DirectionType::TOP].SetEnabled(false);
		scrollButton[(int)DirectionType::BOTTOM].SetEnabled(true);
	}

	if (scrollButton[(int)DirectionType::BOTTOM].GetMouseSelected() || (mouseHit && scrollVertical && Input::MouseInput::GetWheelRot() < 0.f) && enabled && ObjectOverlapping::GetGUIDForCanvas() == guid) {
		if (scrollValue.y + distance > 1.001f) {
			distance = 1.f - scrollValue.y;
		}
		scrollValue.y += distance;
		Move(PosVec(0.f, -distance * (scrollDistance.y - size.y)), false);
		if (parent != nullptr) {
			if (parent->GetCanvasOwner())
				parent->Move(PosVec(0.f, distance * (scrollDistance.y - size.y), 0.f));
		}
		for (auto& item : scrollButton) {
			item.Move(PosVec(0.f, distance * (scrollDistance.y - size.y), 0.f));
		}
		for (auto& item : scrollBar) {
			item.Move(PosVec(0.f, distance * (scrollDistance.y - size.y), 0.f));
		}
		scrollButton[(int)DirectionType::BOTTOM].SetMouseOff();
		scrollBar[0].SetValue(scrollValue.y);

		if (scrollValue.y >= 0.9999f) scrollButton[(int)DirectionType::BOTTOM].SetEnabled(false);
		scrollButton[(int)DirectionType::TOP].SetEnabled(true);
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
	DrawBoxAA(pos.x, pos.y, pos.x + scrollDistance.x, pos.y + scrollDistance.y, innerAnimation.current.Get(), true, 0.f);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawScreen(DX_SCREEN_BACK);

}

void CanvasObject::Draw()
{
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
	if (parent != nullptr) {
		if (parent->GetCanvasOwner())
			SetDrawScreen(parent->GetCanvasId());
		else
			SetDrawScreen(DX_SCREEN_BACK);
	}
	else {
		SetDrawScreen(DX_SCREEN_BACK);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRectGraphF(pos.x, pos.y, (int)pos.x, (int)pos.y, (int)size.x, (int)size.y, canvasId, true, false);

	for (auto& item : scrollButton) {
		item.Draw();
	}

	for (auto& item : scrollBar) {
		item.Draw();
	}

	SetDrawScreen(DX_SCREEN_BACK);

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

bool CanvasObject::RegisterCanvas(ObjectBase* _object)
{
	_object->RegisterParent(this);
	ObjectBase::RegisterChildren(_object);
	return false;
}

void CanvasObject::CollideMouse()
{
	if (!enabled) return;

	if (pos.x <= Input::MouseInput::GetMouse().x &&
		pos.x + size.x >= Input::MouseInput::GetMouse().x &&
		pos.y <= Input::MouseInput::GetMouse().y &&
		pos.y + size.y >= Input::MouseInput::GetMouse().y) {

		mouseHit = true;
		ObjectOverlapping::UpdateObjectForCanvas(guid);
	}
	else {
		mouseHit = false;
	}

}
