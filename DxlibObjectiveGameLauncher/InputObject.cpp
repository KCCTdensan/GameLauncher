#include "InputObject.h"

void InputObject::Collide()
{
	CollideMouseAsBox();
	textObject->Collide();
}

void InputObject::Update()
{
	CheckGUID();
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

		if (!interruptMode) {
			// アクティブ
			if (GetActiveKeyInput() != inputHandle && !turnedOn) {
				SetActiveKeyInput(inputHandle);
				turnedOn = true;
			}

			char text[inputStringMax] = "";
			try {
				GetKeyInputString(text, inputHandle);
			}
			catch (std::exception e) {
				// printfDx("Exception\n");
			}
			inputText = text;

			if (turnedOn) {
				if (Input::KeyboardInput::KEY[KEY_INPUT_LALT] == 1) {
					SetString(inputText + "\n");
				}
				if (Input::KeyboardInput::KEY[KEY_INPUT_LCONTROL] > 1 && Input::KeyboardInput::KEY[KEY_INPUT_UP] == 1) {
					writingOffset.y += 15.f;
				}
				if (Input::KeyboardInput::KEY[KEY_INPUT_LCONTROL] > 1 && Input::KeyboardInput::KEY[KEY_INPUT_DOWN] == 1) {
					writingOffset.y -= 15.f;
				}
			}
		}
		else {
			char text[inputStringMax] = "";
			textObject->SetText("");
			Draw();
			try {
				KeyInputString((int)pos.x, (int)pos.y, inputStringMax, text, true);
			}
			catch (std::exception e) {
				// printfDx("Exception\n");
			}
			inputText = text;
			textObject->SetText(inputText);
			SetMouseOff();
		}
	}
	else {
		if (GetActiveKeyInput() == inputHandle && turnedOn) {
			SetActiveKeyInput(-1);
			SetMouseOff();
			turnedOn = false;
			textObject->SetPos(pos);
			textObject->SetText(inputText);
			textObject->Move(PosVec(textObject->GetFinallyPos().x - pos.x, textObject->GetFinallyPos().y - pos.y, textObject->GetFinallyPos().z - pos.z));
		}
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

	UpdateAnimationColor(&innerAnimation);
	UpdateAnimationColor(&outerAnimation);
	UpdateAnimation(&innerAlphaAnimation);
	UpdateAnimation(&outerAlphaAnimation);

	UpdatePointerAnimation();

	if (GetActiveKeyInput() != inputHandle && turnedOn) {
		if (CheckKeyInput(inputHandle) != 0) {
			SetActiveKeyInput(-1);
			SetMouseOff();
			turnedOn = false;
			textObject->SetPos(pos);
			textObject->SetText(inputText);
			textObject->Move(PosVec(textObject->GetFinallyPos().x - pos.x, textObject->GetFinallyPos().y - pos.y, textObject->GetFinallyPos().z - pos.z));
		}
	}

	if (!turnedOn) writingOffset = PosVec();

	textObject->Update();
}

void InputObject::Draw()
{
	if (canvasId != -1) {
		SetDrawScreen(canvasId);
	}
	else {
		SetDrawScreen(DX_SCREEN_BACK);
	}
	SetDrawArea((int)pos.x, (int)pos.y, (int)(pos.x + size.x + 1), (int)(pos.y + size.y + 1));
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
	if (!turnedOn)
		textObject->Draw();
	SetDrawArea(0, 0, (int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y);
	if (turnedOn) {
		SetDrawArea(0, 0, (int)(pos.x + size.x + 1), (int)ApplicationPreference::GetBackgroundSize().y);
		DrawKeyInputString((int)pos.x + (int)writingOffset.x, (int)pos.y + (int)writingOffset.y, inputHandle);
		DrawKeyInputModeString((int)pos.x, (int)(pos.y + size.y));
	}
	SetDrawScreen(DX_SCREEN_BACK);
}

void InputObject::CollideMouse()
{}