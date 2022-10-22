#pragma once
#include "ObjectBase.h"
#include "TextAlign.h"
#include <string>
#include "DxLib.h"
#include "FontChest.h"

class TextObject :
	public ObjectBase
{
public:
	// sizeは無視される
	TextObject(PosVec _pos, PosVec _size, int _fontHandle, std::string _text, Color255 _innerColor = 0, TextAlign _align = TextAlign::LEFT, bool _enabledBack = false)
		: ObjectBase(_pos, PosVec()), fontHandle(_fontHandle), fontHandleName(), text(_text), innerColor(_innerColor), align(_align),
		enabledBack(_enabledBack), backColor(0), textWidth(0), fontHeight(0), adjusted(false),
		finallyPos(_pos), paddingUpperLeft(PosVec()), paddingLowerRight(PosVec()), fontAutoSerching(false), maxWidth(-1), returnNum(0),
		forcedAreaMode(false), originalText(_text)
	{
		CalcPos();
	}

	// sizeは無視される
	// フォントハンドル自動検索
	TextObject(PosVec _pos, PosVec _size, std::string _fontHandleName, std::string _text, Color255 _innerColor = 0, TextAlign _align = TextAlign::LEFT, bool _enabledBack = false)
		: ObjectBase(_pos, PosVec()), fontHandle(-1), fontHandleName(_fontHandleName), text(_text), innerColor(_innerColor), align(_align),
		enabledBack(_enabledBack), backColor(0), textWidth(0), fontHeight(0), adjusted(false),
		finallyPos(_pos), paddingUpperLeft(PosVec()), paddingLowerRight(PosVec()), fontAutoSerching(true), maxWidth(-1), returnNum(0),
		forcedAreaMode(false), originalText(_text)
	{
		CalcPos();
	}

	TextObject()
		: ObjectBase(PosVec(), PosVec()), fontHandle(-1), fontHandleName(), text(), innerColor(0), align(TextAlign::LEFT), enabledBack(false), backColor(0),
		finallyPos(PosVec()), textWidth(0), fontHeight(0), paddingUpperLeft(PosVec()), paddingLowerRight(PosVec()), fontAutoSerching(false), maxWidth(-1), adjusted(false), returnNum(0),
		forcedAreaMode(false), originalText()
	{}

	// 文字情報登録
	bool SetText(std::string _text) { text = _text; originalText = _text; CalcPos(); adjusted = false; return true; }
	bool SetFontHandle(int _fontHandle) { fontHandle = _fontHandle; CalcPos();  return true; }
	int SetFontHandle() { return fontHandle; }

	bool SetEnabledBack(bool _enabledBack) { enabledBack = _enabledBack; return true; }
	bool SetEnabledBack() { return enabledBack; }

	// 色情報登録等
	bool SetInnerColor(Color255 _innerColor, bool _defaultFill = true)
	{
		innerColor = _innerColor;
		if (_defaultFill) {
			innerAnimation.current = innerColor;
			innerAlphaAnimation.current = (float)innerColor.a;
		}
		return true;
	}
	bool SetBackColor(Color255 _backColor) { backColor = _backColor; return true; }

	bool SetOffForcedArea() { forcedAreaMode = false; return true; }
	bool SetForcedArea(PosVec _areaUpperLeft, PosVec _areaLowerRight)
	{
		forcedAreaMode = true;
		areaUpperLeft = _areaUpperLeft;
		areaLowerRight = _areaLowerRight;
		return true;
	}

	// Padding設定(enabledBackのみ有効)
	// trueの場合無視
	bool SetPadding(bool _flag) { if (!_flag) { paddingUpperLeft = PosVec(); paddingLowerRight = PosVec(); } return true; }
	bool SetPadding(float _top, float _right, float _bottom, float _left) { paddingUpperLeft = PosVec(_left, _top); paddingLowerRight = PosVec(_right, _bottom); return true; }
	bool SetPadding(float _vertical, float _horizontal) { paddingUpperLeft = PosVec(_horizontal, _vertical); paddingLowerRight = PosVec(_horizontal, _vertical); return true; }
	bool SetPadding(float _value) { paddingUpperLeft = PosVec(_value, _value); paddingLowerRight = PosVec(_value, _value); return true; }

	bool SetMaxWidth(int _value) {maxWidth = _value >= 1 ? _value : -1;	return true;}

	std::string GetText() { return text; }
	std::string GetOriginalText() { return originalText; }

	int GetTextWidth() { return textWidth; }
	PosVec GetFinallyPos() { return finallyPos; }

	int GetTextHeight() { return ((returnNum + 1) * GetFontSizeToHandle(fontHandle)); }
	int GetFontHeight() { return GetFontSizeToHandle(fontHandle); }

	Color255* GetColor(ColorType type) {
		switch (type)
		{
		case ColorType::INNER:
			return &innerColor;
		default:
			return nullptr;
		}
	}

	bool Move(PosVec _delta, bool _involvedParent = true) override;

	// 描画開始位置を計算
	void CalcPos();

	// 更新描画
	void Collide() override {}
	void Update() override;
	void Draw() override;

private:

	std::wstring ConvertString(const std::string& input)
	{
		size_t i;
		wchar_t* buffer = new wchar_t[input.size() + 1];
		mbstowcs_s(&i, buffer, input.size() + 1, input.c_str(), _TRUNCATE);
		std::wstring result = buffer;
		delete[] buffer;
		return result;
	}
	std::string ConvertString(const std::wstring& input)
	{
		size_t i;
		char* buffer = new char[input.size() * MB_CUR_MAX + 1];
		wcstombs_s(&i, buffer, input.size() * MB_CUR_MAX + 1, input.c_str(), _TRUNCATE);
		std::string result = buffer;
		delete[] buffer;
		return result;
	}

	// ハンドル探し
	void FontSerch();

private:

	void CollideMouse() override {}

private:
	int fontHandle;
	std::string fontHandleName;
	bool fontAutoSerching;
	std::string text;
	std::string originalText;
	int textWidth;
	int fontHeight;

	int returnNum;

	PosVec areaUpperLeft;
	PosVec areaLowerRight;
	bool forcedAreaMode;

	PosVec paddingUpperLeft;
	PosVec paddingLowerRight;

	PosVec finallyPos;

	Color255 innerColor;

	TextAlign align;

	Color255 backColor;

	bool enabledBack;

	int maxWidth;

	bool adjusted;
};

