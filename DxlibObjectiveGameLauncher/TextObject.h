#pragma once
#include "ObjectBase.h"
#include "TextAlign.h"
#include <string>
#include "DxLib.h"

class TextObject :
	public ObjectBase
{
public:
	// size‚Í–³‹‚³‚ê‚é
	TextObject(PosVec _pos, PosVec _size, int _fontHandle, std::string _text, int _innerColor = 0, TextAlign _align = TextAlign::LEFT, bool _enabledBack = false)
		: ObjectBase(_pos, _size), fontHandle(_fontHandle), text(_text), innerColor(_innerColor), align(_align),
		enabledBack(_enabledBack), backColor(0), textWidth(0), fontHeight(0),
		finallyPos(_pos), paddingUpperLeft(PosVec()), paddingLowerRight(PosVec())
	{
		CalcPos();
	}

	TextObject()
		: ObjectBase(PosVec(), PosVec()), fontHandle(-1), text(), innerColor(0), align(TextAlign::LEFT), enabledBack(false), backColor(0),
		finallyPos(PosVec()), textWidth(0), fontHeight(0), paddingUpperLeft(PosVec()), paddingLowerRight(PosVec())
	{}

	// •¶šî•ñ“o˜^
	bool SetText(std::string _text) { text = _text; CalcPos(); return true; }
	bool SetFontHandle(int _fontHandle) { fontHandle = _fontHandle; CalcPos();  return true; }
	int SetFontHandle() { return fontHandle; }

	bool SetEnabledBack(bool _enabledBack) { enabledBack = _enabledBack; return true; }
	bool SetEnabledBack() { return enabledBack; }

	// Fî•ñ“o˜^“™
	bool SetInnerColor(int _innerColor) { innerColor = _innerColor; return true; }
	bool SetBackColor(int _backColor) { backColor = _backColor; return true; }

	// Paddingİ’è(enabledBack‚Ì‚İ—LŒø)
	// true‚Ìê‡–³‹
	bool SetPadding(bool _flag) { if (!_flag) { paddingUpperLeft = PosVec(); paddingLowerRight = PosVec(); } return true; }
	bool SetPadding(float _top, float _right, float _bottom, float _left) { paddingUpperLeft = PosVec(_left, _top); paddingLowerRight = PosVec(_right, _bottom); return true; }
	bool SetPadding(float _vertical, float _horizontal) { paddingUpperLeft = PosVec(_horizontal, _vertical); paddingLowerRight = PosVec(_horizontal, _vertical); return true; }
	bool SetPadding(float _value) { paddingUpperLeft = PosVec(_value, _value); paddingLowerRight = PosVec(_value, _value); return true; }

	// XV•`‰æ
	void Collide() {}
	void Update();
	void Draw();

private:

	// •`‰æŠJnˆÊ’u‚ğŒvZ
	void CalcPos();

private:
	int fontHandle;
	std::string text;
	int textWidth;
	int fontHeight;

	PosVec paddingUpperLeft;
	PosVec paddingLowerRight;

	PosVec finallyPos;

	int innerColor;
	TextAlign align;

	int backColor;

	bool enabledBack;
};

