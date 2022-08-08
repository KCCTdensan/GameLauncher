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
	// size�͖��������
	TextObject(PosVec _pos, PosVec _size, int _fontHandle, std::string _text, Color255 _innerColor = 0, TextAlign _align = TextAlign::LEFT, bool _enabledBack = false)
		: ObjectBase(_pos, PosVec()), fontHandle(_fontHandle), fontHandleName(), text(_text), innerColor(_innerColor), align(_align),
		enabledBack(_enabledBack), backColor(0), textWidth(0), fontHeight(0),
		finallyPos(_pos), paddingUpperLeft(PosVec()), paddingLowerRight(PosVec()), fontAutoSerching(false)
	{
		CalcPos();
	}

	// size�͖��������
	// �t�H���g�n���h����������
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

	// �������o�^
	bool SetText(std::string _text) { text = _text; CalcPos(); return true; }
	bool SetFontHandle(int _fontHandle) { fontHandle = _fontHandle; CalcPos();  return true; }
	int SetFontHandle() { return fontHandle; }

	bool SetEnabledBack(bool _enabledBack) { enabledBack = _enabledBack; return true; }
	bool SetEnabledBack() { return enabledBack; }

	// �F���o�^��
	bool SetInnerColor(Color255 _innerColor) { innerColor = _innerColor; return true; }
	bool SetBackColor(Color255 _backColor) { backColor = _backColor; return true; }

	// Padding�ݒ�(enabledBack�̂ݗL��)
	// true�̏ꍇ����
	bool SetPadding(bool _flag) { if (!_flag) { paddingUpperLeft = PosVec(); paddingLowerRight = PosVec(); } return true; }
	bool SetPadding(float _top, float _right, float _bottom, float _left) { paddingUpperLeft = PosVec(_left, _top); paddingLowerRight = PosVec(_right, _bottom); return true; }
	bool SetPadding(float _vertical, float _horizontal) { paddingUpperLeft = PosVec(_horizontal, _vertical); paddingLowerRight = PosVec(_horizontal, _vertical); return true; }
	bool SetPadding(float _value) { paddingUpperLeft = PosVec(_value, _value); paddingLowerRight = PosVec(_value, _value); return true; }

	// �X�V�`��
	void Collide() {}
	void Update();
	void Draw();

private:

	// �`��J�n�ʒu���v�Z
	void CalcPos();

	// �n���h���T��
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

