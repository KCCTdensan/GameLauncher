#include "TextObject.h"

void TextObject::Update()
{
	UpdateEnforcedMouseCollision();

	if (fontAutoSerching) FontSerch();

	SetAnimationColorPoint(&innerAnimation, innerAnimation.current, innerColor);
	SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)innerColor.a);

	if (maxWidth > 0 && !adjusted) {
		int sum = 0;
		std::vector<int> index = {};
		int v = 0;
		returnNum = 0;
		std::wstring wText = ConvertString(text);
		for (v = 0; v < wText.size(); v++) {
			std::string letter = ConvertString(wText.substr(v, 1));
			if (letter == "\n") {
				sum = 0;
				returnNum++;
				continue;
			}
			int newWidth = GetDrawStringWidthToHandle(letter.c_str(), 2, fontHandle);
			sum += newWidth;
			if (sum > maxWidth) {
				sum = newWidth;
				index.push_back(v);
			}
		}
		std::reverse(index.begin(), index.end());
		for (auto i : index) {
			wText.insert(i, L"\n");
			returnNum++;
		}
		text = ConvertString(wText);
		adjusted = true;
	}
	UpdateAnimationColor(&innerAnimation);
	UpdateAnimation(&innerAlphaAnimation);
	UpdatePointerAnimation();
}

void TextObject::Draw()
{
	if (!enabled) return;
	if (canvasId != -1) {
		SetDrawScreen(canvasId);
	}
	else {
		SetDrawScreen(DX_SCREEN_BACK);
	}
	if (forcedAreaMode)
		SetDrawArea((int)areaUpperLeft.x, (int)areaUpperLeft.y, (int)areaLowerRight.x, (int)areaLowerRight.y);
	if (enabledBack) {
		DrawBoxAA(finallyPos.x - paddingUpperLeft.x, finallyPos.y - paddingUpperLeft.y, finallyPos.x + textWidth + paddingLowerRight.x, finallyPos.y + fontHeight + paddingLowerRight.y, backColor.Get(), true);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)innerAlphaAnimation.current);
	DrawFormatStringFToHandle(finallyPos.x, finallyPos.y, innerAnimation.current.Get(), fontHandle, text.c_str());
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawArea(0, 0, (int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y);
}

bool TextObject::Move(PosVec _delta, bool _involvedParent)
{
	ObjectBase::Move(_delta, _involvedParent);
	areaUpperLeft.x += _delta.x;
	areaUpperLeft.y += _delta.y;
	areaLowerRight.x += _delta.x;
	areaLowerRight.y += _delta.y;
	CalcPos();

	return true;
}

void TextObject::CalcPos()
{
	GetFontStateToHandle(NULL, &fontHeight, NULL, fontHandle);
	textWidth = GetDrawStringWidthToHandle(text.c_str(), (int)text.size(), fontHandle);

	switch (align)
	{
	case TextAlign::LEFT:
		finallyPos.x = pos.x;
		finallyPos.y = pos.y;
		break;
	case TextAlign::CENTER:
		finallyPos.x = pos.x - (float)textWidth / 2.f;
		finallyPos.y = pos.y;
		break;
	case TextAlign::RIGHT:
		finallyPos.x = pos.x - (float)textWidth;
		finallyPos.y = pos.y;
		break;
	default:
		finallyPos.x = pos.x;
		finallyPos.y = pos.y;
		break;
	}
}

void TextObject::FontSerch()
{
	SetFontHandle(FontChest::GetFontHandle(fontHandleName));
	if (fontHandle > 0) fontAutoSerching = false;
}

void TextObject::DeleteNewLine()
{
	std::wstring wText = ConvertString(text);
	std::wstring chars = L"\n";
	for (auto& c : chars) {
		wText.erase(std::remove(wText.begin(), wText.end(), c), wText.end());
	}
	text = ConvertString(wText);
}
