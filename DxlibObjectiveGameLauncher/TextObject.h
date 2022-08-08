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
		enabledBack(_enabledBack), backColor(0), textWidth(0), fontHeight(0),
		finallyPos(_pos), paddingUpperLeft(PosVec()), paddingLowerRight(PosVec()), fontAutoSerching(false)
	{
		CalcPos();
	}

	// sizeは無視される
	// フォントハンドル自動検索
	TextObject(PosVec _pos, PosVec _size, std::string _fontHandleName, std::string _text, Color255 _innerColor = 0, TextAlign _align = TextAlign::LEFT, bool _enabledBack = false)
		: ObjectBase(_pos, PosVec()), fontHandle(-1), fontHandleName(_fontHandleName), text(_text), innerColor(_innerColor), align(_align),
		enabledBack(_enabledBack), backColor(0), textWidth(0), fontHeight(0),
		finallyPos(_pos), paddingUpperLeft(PosVec()), paddingLowerRight(PosVec()), fontAutoSerching(true)
	{
		CalcPos();
	}

	TextObject()
		: ObjectBase(PosVec(), PosVec()), fontHandle(-1), fontHandleName(), text(), innerColor(0), align(TextAlign::LEFT), enabledBack(false), backColor(0),
		finallyPos(PosVec()), textWidth(0), fontHeight(0), paddingUpperLeft(PosVec()), paddingLowerRight(PosVec()), fontAutoSerching(false)
	{}

	// 文字情報登録
	bool SetText(std::string _text) { text = _text; CalcPos(); return true; }
	bool SetFontHandle(int _fontHandle) { fontHandle = _fontHandle; CalcPos();  return true; }
	int SetFontHandle() { return fontHandle; }

	bool SetEnabledBack(bool _enabledBack) { enabledBack = _enabledBack; return true; }
	bool SetEnabledBack() { return enabledBack; }

	// 色情報登録等
	bool SetInnerColor(Color255 _innerColor) { innerColor = _innerColor; return true; }
	bool SetBackColor(Color255 _backColor) { backColor = _backColor; return true; }

	// Padding設定(enabledBackのみ有効)
	// trueの場合無視
	bool SetPadding(bool _flag) { if (!_flag) { paddingUpperLeft = PosVec(); paddingLowerRight = PosVec(); } return true; }
	bool SetPadding(float _top, float _right, float _bottom, float _left) { paddingUpperLeft = PosVec(_left, _top); paddingLowerRight = PosVec(_right, _bottom); return true; }
	bool SetPadding(float _vertical, float _horizontal) { paddingUpperLeft = PosVec(_horizontal, _vertical); paddingLowerRight = PosVec(_horizontal, _vertical); return true; }
	bool SetPadding(float _value) { paddingUpperLeft = PosVec(_value, _value); paddingLowerRight = PosVec(_value, _value); return true; }

	// 更新描画
	void Collide() {}
	void Update();
	void Draw();

private:

	// 描画開始位置を計算
	void CalcPos();

	// ハンドル探し
	void FontSerch();

private:
	int fontHandle;
	std::string fontHandleName;
	bool fontAutoSerching;
	std::string text;
	int textWidth;
	int fontHeight;

	PosVec paddingUpperLeft;
	PosVec paddingLowerRight;

	PosVec finallyPos;

	Color255 innerColor;
	TextAlign align;

	Color255 backColor;

	bool enabledBack;
};

