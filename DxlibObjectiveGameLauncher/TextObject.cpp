#include "TextObject.h"

void TextObject::Update()
{
}

void TextObject::Draw()
{
	if (enabledBack) {
		DrawBoxAA(finallyPos.x - paddingUpperLeft.x, finallyPos.y - paddingUpperLeft.y, finallyPos.x + textWidth + paddingLowerRight.x, finallyPos.y + fontHeight + paddingLowerRight.y, backColor, true);
		OutputDebugString("aaaa");
	}
	DrawFormatStringFToHandle(finallyPos.x, finallyPos.y, innerColor, fontHandle, text.c_str());
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
