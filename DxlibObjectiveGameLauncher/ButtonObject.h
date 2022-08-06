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
		innerColorAlpha(255), hoveredInnerColorAlpha(255), clickedInnerColorAlpha(255), selectedInnerColorAlpha(255),
		outerColorAlpha(255), hoveredOuterColorAlpha(255), clickedOuterColorAlpha(255), selectedOuterColorAlpha(255),
		outlineWidth(0)
	{}

	ButtonObject()
		: ObjectBase(PosVec(), PosVec()), enabledFill(true), enabledOutline(false),
		innerColor(0), selectedInnerColor(0), hoveredInnerColor(0), clickedInnerColor(0),
		outerColor(0), selectedOuterColor(0), hoveredOuterColor(0), clickedOuterColor(0),
		innerColorAlpha(255), hoveredInnerColorAlpha(255), clickedInnerColorAlpha(255), selectedInnerColorAlpha(255),
		outerColorAlpha(255), hoveredOuterColorAlpha(255), clickedOuterColorAlpha(255), selectedOuterColorAlpha(255),
		outlineWidth(0)
	{}

	// êFóLå¯âªñ≥å¯âª
	bool SetEnabledFill(bool _enabled) { enabledFill = _enabled; return true; }
	bool SetEnabledFill() { return enabledFill; }
	bool SetEnabledOutline(bool _enabled, float _outlineWidth = 1) { enabledOutline = _enabled; outlineWidth = (enabledOutline) ? _outlineWidth : 0; return true; }
	bool SetEnabledOutline() { return enabledOutline; }

	// êFèÓïÒìoò^ìô
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

	void SetInnerAlpha(int _alpha)
	{
		innerColorAlpha = _alpha;
		hoveredInnerColorAlpha = _alpha;
		clickedInnerColorAlpha = _alpha;
		selectedInnerColorAlpha = _alpha;
	}
	void SetInnerAlpha(int _alpha, int _hoveredAlpha, int _clickedAlpha, int selectedAlpha)
	{
		innerColorAlpha = _alpha;
		hoveredInnerColorAlpha = _hoveredAlpha;
		clickedInnerColorAlpha = _clickedAlpha;
		selectedInnerColorAlpha = selectedAlpha;
	}
	void SetOuterAlpha(int _alpha)
	{
		outerColorAlpha = _alpha;
		hoveredOuterColorAlpha = _alpha;
		clickedOuterColorAlpha = _alpha;
		selectedOuterColorAlpha = _alpha;
	}
	void SetOuterAlpha(int _alpha, int _hoveredAlpha, int _clickedAlpha, int selectedAlpha)
	{
		outerColorAlpha = _alpha;
		hoveredOuterColorAlpha = _hoveredAlpha;
		clickedOuterColorAlpha = _clickedAlpha;
		selectedOuterColorAlpha = selectedAlpha;
	}


	// çXêVï`âÊ
	void Collide();
	void Update();
	void Draw();

private:

	void CollideMouse();

private:
	int innerColorAlpha;
	int hoveredInnerColorAlpha;
	int clickedInnerColorAlpha;
	int selectedInnerColorAlpha;
	int outerColorAlpha;
	int hoveredOuterColorAlpha;
	int clickedOuterColorAlpha;
	int selectedOuterColorAlpha;

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


};

