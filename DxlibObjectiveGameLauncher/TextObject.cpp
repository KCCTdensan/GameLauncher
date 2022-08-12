#include "TextObject.h"

void TextObject::Update()
{
	CheckGUID();

	if (fontAutoSerching) FontSerch();

	if (maxWidth > 0 && !adjusted) {
		int sum = 0;
		std::vector<int> index = {};
		int v = 0;
		std::wstring wText = ConvertString(text);
		for (v = 0; v < wText.size(); v++) {
			std::string letter = ConvertString(wText.substr(v, 1));
			if (letter == "\n") {
				sum = 0;
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
		}
		text = ConvertString(wText);
		adjusted = true;
	}

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
	if (enabledBack) {
		DrawBoxAA(finallyPos.x - paddingUpperLeft.x, finallyPos.y - paddingUpperLeft.y, finallyPos.x + textWidth + paddingLowerRight.x, finallyPos.y + fontHeight + paddingLowerRight.y, backColor.Get(), true);
	}
	DrawFormatStringFToHandle(finallyPos.x, finallyPos.y, innerColor.Get(), fontHandle, text.c_str());
	SetDrawScreen(DX_SCREEN_BACK);
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
