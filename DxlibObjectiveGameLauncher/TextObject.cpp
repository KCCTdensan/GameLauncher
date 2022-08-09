#include "TextObject.h"

void TextObject::Update()
{
	CheckGUID();

	if (fontAutoSerching) FontSerch();

	int sum = 0;

	if (maxWidth > 0 && !adjusted) {
		std::vector<int> index = {};
		int v = 0;
		for (std::string::iterator it = text.begin(); it != text.end(); ++it, v++) {
			TCHAR letter = *it;
			if (&letter == "\n") {
				sum = 0;
				continue;
			}
			sum += GetDrawStringWidthToHandle(&letter, 1, fontHandle);

			if (sum > maxWidth) {
				sum = 0;
				index.push_back(v);
			}
		}
		std::reverse(index.begin(), index.end());
		for (auto i : index) {
			text.insert(i, "\n");
		}
		adjusted = true;
	}
}

void TextObject::Draw()
{
	if (enabledBack) {
		DrawBoxAA(finallyPos.x - paddingUpperLeft.x, finallyPos.y - paddingUpperLeft.y, finallyPos.x + textWidth + paddingLowerRight.x, finallyPos.y + fontHeight + paddingLowerRight.y, backColor.Get(), true);
	}
	DrawFormatStringFToHandle(finallyPos.x, finallyPos.y, innerColor.Get(), fontHandle, text.c_str());
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
