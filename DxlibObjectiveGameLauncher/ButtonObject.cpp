#include "ButtonObject.h"

void ButtonObject::Collide()
{
	CollideMouseAsBox();
	if (textObject != nullptr)
		textObject->Collide();
}

void ButtonObject::Update()
{
	CheckGUID();
	UpdateEnforcedMouseCollision();

	// アニメーション記述をする場合，ここに記述
	if (mouseHit) {
		SetAnimationColorPoint(&innerAnimation, innerAnimation.current, hoveredInnerColor);
		SetAnimationColorPoint(&outerAnimation, outerAnimation.current, hoveredOuterColor);
		SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)hoveredInnerColor.a);
		SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)hoveredOuterColor.a);
		SetAnimationPoint(&imageAlphaAnimation, (float)imageAlphaAnimation.current, (float)hoveredImageColor.a);
	}
	else {
		SetAnimationColorPoint(&innerAnimation, innerAnimation.current, innerColor);
		SetAnimationColorPoint(&outerAnimation, outerAnimation.current, outerColor);
		SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)innerColor.a);
		SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)outerColor.a);
		SetAnimationPoint(&imageAlphaAnimation, (float)imageAlphaAnimation.current, (float)defaultImageColor.a);
	}

	if (mouseSelected) {
		SetAnimationColorPoint(&innerAnimation, innerAnimation.current, selectedInnerColor);
		SetAnimationColorPoint(&outerAnimation, outerAnimation.current, selectedOuterColor);
		SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)selectedInnerColor.a);
		SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)selectedOuterColor.a);
		SetAnimationPoint(&imageAlphaAnimation, (float)imageAlphaAnimation.current, (float)selectedImageColor.a);
	}

	if (mouseClicked) {
		SetAnimationColorPoint(&innerAnimation, innerAnimation.current, clickedInnerColor);
		SetAnimationColorPoint(&outerAnimation, outerAnimation.current, clickedOuterColor);
		SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)clickedInnerColor.a);
		SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)clickedOuterColor.a);
		SetAnimationPoint(&imageAlphaAnimation, (float)imageAlphaAnimation.current, (float)clickedImageColor.a);
	}

	if (!enabled) {
		SetAnimationColorPoint(&innerAnimation, innerAnimation.current, disabledInnerColor);
		SetAnimationColorPoint(&outerAnimation, outerAnimation.current, disabledOuterColor);
		SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)disabledInnerColor.a);
		SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)disabledOuterColor.a);
		SetAnimationPoint(&imageAlphaAnimation, (float)imageAlphaAnimation.current, (float)disabledImageColor.a);
	}

	EventRectSetVector();
	if (textObject != nullptr)
		textObject->Update();

	UpdateAnimationColor(&innerAnimation);
	UpdateAnimationColor(&outerAnimation);
	UpdateAnimation(&innerAlphaAnimation);
	UpdateAnimation(&outerAlphaAnimation);
	UpdateAnimation(&imageAlphaAnimation); // 画像alpha値

	UpdatePointerAnimation();
}

void ButtonObject::Draw()
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
	if (rectMode) eventRect.Draw();

	DrawImage();

	if (textObject != nullptr)
		textObject->Draw();

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

void ButtonObject::CollideMouse()
{}

void ButtonObject::EventRectSetVector()
{
	if (rectMode && rectEventEnabled != nullptr) {
		if (*rectEventEnabled) {
			eventRect.ChangeValueWithAnimation(
				&(eventRect.GetVectorPointer(VectorType::POS)->x),
				pos.x,
				innerAnimation.duration
			);
			eventRect.ChangeValueWithAnimation(
				&(eventRect.GetVectorPointer(VectorType::POS)->y),
				pos.y,
				innerAnimation.duration
			);
			eventRect.ChangeValueWithAnimation(
				&(eventRect.GetVectorPointer(VectorType::SIZE)->x),
				size.x,
				innerAnimation.duration
			);
			eventRect.ChangeValueWithAnimation(
				&(eventRect.GetVectorPointer(VectorType::SIZE)->y),
				size.y,
				innerAnimation.duration
			);
		}
		else {
			switch (rectDirectionFrom)
			{
			case DirectionType::TOP:
				eventRect.ChangeValueWithAnimation(
					&(eventRect.GetVectorPointer(VectorType::SIZE)->y),
					0.f,
					innerAnimation.duration
				);
				break;
			case DirectionType::BOTTOM:
				eventRect.ChangeValueWithAnimation(
					&(eventRect.GetVectorPointer(VectorType::SIZE)->y),
					0.f,
					innerAnimation.duration
				);
				eventRect.ChangeValueWithAnimation(
					&(eventRect.GetVectorPointer(VectorType::POS)->y),
					pos.y + size.y,
					innerAnimation.duration
				);
				break;
			case DirectionType::LEFT:
				eventRect.ChangeValueWithAnimation(
					&(eventRect.GetVectorPointer(VectorType::SIZE)->x),
					0.f,
					innerAnimation.duration
				);
				break;
			case DirectionType::RIGHT:
				eventRect.ChangeValueWithAnimation(
					&(eventRect.GetVectorPointer(VectorType::SIZE)->x),
					0.f,
					innerAnimation.duration
				);
				eventRect.ChangeValueWithAnimation(
					&(eventRect.GetVectorPointer(VectorType::POS)->x),
					pos.x + size.x,
					innerAnimation.duration
				);
				break;
			default:
				break;
			}
		}
		eventRect.Update();
	}
}