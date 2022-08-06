#pragma once
#include "ObjectBase.h"
#include "DxLib.h"
#include "MouseInput.h"
#include "ObjectOverlapping.h"
#include "PressFrameEnum.h"
#include <string>

class ButtonObject :
	public ObjectBase
{
public:
	ButtonObject(PosVec _pos, PosVec _size, bool _enabledFill = true, bool _enabledOutline = false)
		: ObjectBase(_pos, _size),
		enabledFill(_enabledFill), enabledOutline(_enabledOutline),
		innerColor(0), selectedInnerColor(0), hoveredInnerColor(0), clickedInnerColor(0),
		outerColor(0), selectedOuterColor(0), hoveredOuterColor(0), clickedOuterColor(0),
		outlineWidth(0)
	{}

	ButtonObject()
		: ObjectBase(PosVec(), PosVec()), enabledFill(true), enabledOutline(false),
		innerColor(0), selectedInnerColor(0), hoveredInnerColor(0), clickedInnerColor(0),
		outerColor(0), selectedOuterColor(0), hoveredOuterColor(0), clickedOuterColor(0),
		outlineWidth(0)
	{}

	// 色有効化無効化
	bool SetEnabledFill(bool _enabled) { enabledFill = _enabled; return true; }
	bool SetEnabledFill() { return enabledFill; }
	bool SetEnabledOutline(bool _enabled, float _outlineWidth = 1) { enabledOutline = _enabled; outlineWidth = (enabledOutline) ? _outlineWidth : 0; return true; }
	bool SetEnabledOutline() { return enabledOutline; }

	// 色情報登録等
	bool SetInnerColor(Color255 _innerColor, bool _defaultFill = true)
	{
		innerColor = _innerColor;
		hoveredInnerColor = _innerColor;
		clickedInnerColor = _innerColor;
		selectedInnerColor = _innerColor;
		if (_defaultFill) currentInnerColor = innerColor;
		return true;
	}
	bool SetInnerColor(Color255 _innerColor, Color255 _hoveredColor, Color255 _clickedColor, Color255 _selectedColor, bool _defaultFill = true)
	{
		innerColor = _innerColor;
		hoveredInnerColor = _hoveredColor;
		clickedInnerColor = _clickedColor;
		selectedInnerColor = _selectedColor;
		if (_defaultFill) currentInnerColor = innerColor;
		return true;
	}
	bool SetOutlineColor(Color255 _outerColor, float _outlineWidth, bool _defaultFill = true) {
		outerColor = _outerColor;
		hoveredOuterColor = _outerColor;
		clickedOuterColor = _outerColor;
		selectedOuterColor = _outerColor;
		outlineWidth = _outlineWidth;
		if (_defaultFill) currentOuterColor = outerColor;
		return true; 
	}
	bool SetOutlineColor(Color255 _outerColor, Color255 _hoveredColor, Color255 _clickedColor, Color255 _selectedColor, float _outlineWidth, bool _defaultFill = true) {
		outerColor = _outerColor;
		hoveredOuterColor = _hoveredColor;
		clickedOuterColor = _clickedColor;
		selectedOuterColor = _selectedColor;
		outlineWidth = _outlineWidth;
		if (_defaultFill) currentOuterColor = outerColor;
		return true;
	}


	// 更新描画
	void Collide();
	void Update();
	void Draw();

private:

	void CollideMouse();

	// アニメーション目標

private:
	Color255 innerColor;
	Color255 hoveredInnerColor;
	Color255 clickedInnerColor;
	Color255 selectedInnerColor;
	Color255 outerColor;
	Color255 hoveredOuterColor;
	Color255 clickedOuterColor;
	Color255 selectedOuterColor;

	float outlineWidth;

	bool enabledFill;
	bool enabledOutline;

	/******************/

};

