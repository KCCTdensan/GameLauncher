#pragma once
#include "ObjectBase.h"
#include "TextAlign.h"
#include <string>
#include "DxLib.h"

class TextObject :
	public ObjectBase
{
public:
	// sizeÇÕñ≥éãÇ≥ÇÍÇÈ
	TextObject(PosVec _pos, PosVec _size, int _fontHandle, std::string _text, int _innerColor = 0, TextAlign _align = TextAlign::LEFT, bool _enabledBack = false)
		: ObjectBase(_pos, _size), fontHandle(_fontHandle), text(_text), innerColor(_innerColor), align(_align),
		enabledBack(_enabledBack), backColor(0), textWidth(0), fontHeight(0),
		finallyPos(_pos)
	{
		CalcPos();
	}

	TextObject()
		: ObjectBase(PosVec(), PosVec()), fontHandle(-1), text(), innerColor(0), align(TextAlign::LEFT), enabledBack(false), backColor(0),
		finallyPos(PosVec()), textWidth(0), fontHeight(0)
	{}

	// ï∂éöèÓïÒìoò^
	bool SetText(std::string _text) { text = _text; CalcPos(); return true; }
	bool SetFontHandle(int _fontHandle) { fontHandle = _fontHandle; CalcPos();  return true; }
	int SetFontHandle() { return fontHandle; }

	bool SetEnabledBack(bool _enabledBack) { enabledBack = _enabledBack; return true; }
	bool SetEnabledBack() { return enabledBack; }

	// êFèÓïÒìoò^ìô
	bool SetInnerColor(int _innerColor) { innerColor = _innerColor; return true; }
	bool SetBackColor(int _backColor) { backColor = _backColor; return true; }

	// çXêVï`âÊ
	void Collide() {}
	void Update();
	void Draw();

private:

	void CalcPos();

private:
	int fontHandle;
	std::string text;
	int textWidth;
	int fontHeight;

	PosVec finallyPos;

	int innerColor;
	TextAlign align;

	int backColor;

	bool enabledBack;
};

