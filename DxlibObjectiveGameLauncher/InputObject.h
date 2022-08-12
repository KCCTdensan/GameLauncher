#pragma once
#include "ObjectBase.h"
#include "TextObject.h"
#include "MouseInput.h"
#include "ObjectOverlapping.h"
#include "PressFrameEnum.h"
#include <string>

class InputObject :
	public ObjectBase
{
public:
	// テキスト表示は SetupText() を用いる
	InputObject(PosVec _pos, PosVec _size, int _maxLength = 512, bool _cancelVaildFlag = true, bool _singleCharOnlyFlag = false, bool _numCharOnlyFlag = false, bool _enabledFill = true, bool _enabledOutline = false)
		: ObjectBase(_pos, _size),
		enabledFill(_enabledFill), enabledOutline(_enabledOutline),
		innerColor(0), selectedInnerColor(0), hoveredInnerColor(0), clickedInnerColor(0),
		outerColor(0), selectedOuterColor(0), hoveredOuterColor(0), clickedOuterColor(0),
		outlineWidth(0), textObject(), turnedOn(false), interruptMode(false),
		maxLength(_maxLength), cancelVaildFlag(_cancelVaildFlag), singleCharOnlyFlag(_singleCharOnlyFlag), numCharOnlyFlag(_numCharOnlyFlag)
	{
		inputHandle = MakeKeyInput(maxLength, cancelVaildFlag, singleCharOnlyFlag, numCharOnlyFlag);
	}

	InputObject()
		: ObjectBase(PosVec(), PosVec()), enabledFill(true), enabledOutline(false),
		innerColor(0), selectedInnerColor(0), hoveredInnerColor(0), clickedInnerColor(0),
		outerColor(0), selectedOuterColor(0), hoveredOuterColor(0), clickedOuterColor(0),
		outlineWidth(0), textObject(), turnedOn(false), interruptMode(false),
		maxLength(2), cancelVaildFlag(true), singleCharOnlyFlag(false), numCharOnlyFlag(false)
	{
		inputHandle = MakeKeyInput(maxLength, cancelVaildFlag, singleCharOnlyFlag, numCharOnlyFlag);
	}

	~InputObject() {
		DeleteKeyInput(inputHandle);
	}

	void SetupText(int _fontHandle, Color255 _innerColor = 0, TextAlign _align = TextAlign::LEFT, bool _enabledBack = false)
	{
		textObject = TextObject(pos, size, _fontHandle, inputText, _innerColor, _align, _enabledBack);
		textObject.SetMaxWidth((int)size.x);
	}
	void SetupText(std::string _fontHandleName, Color255 _innerColor = 0, TextAlign _align = TextAlign::LEFT, bool _enabledBack = false)
	{
		textObject = TextObject(pos, size, _fontHandleName, inputText, _innerColor, _align, _enabledBack);
		RegisterChildren(&textObject);
		textObject.SetMaxWidth((int)size.x);
		textObject.Move(PosVec(textObject.GetFinallyPos().x - pos.x, textObject.GetFinallyPos().y - pos.y, textObject.GetFinallyPos().z - pos.z));
	}

	void SetInterruptMode(bool _flag) { interruptMode = _flag; }
	bool SetInterruptMode() { return interruptMode; }

	TextObject* GetTextObject() { return &textObject; }

	/*
	*
	* 入力中をselectに
	*
	* 入力用にハンドルを追加する
	*
	*/

	// 色有効化無効化
	bool SetEnabledFill(bool _enabled) { enabledFill = _enabled; return true; }
	bool SetEnabledFill() { return enabledFill; }
	bool SetEnabledOutline(bool _enabled, float _outlineWidth = -1.f) { enabledOutline = _enabled; outlineWidth = _outlineWidth ? _outlineWidth <= 0.f : 0.f; return true; }
	// 判定用リターン
	bool SetEnabledOutline() { return enabledOutline; }

	// 色情報登録等
	bool SetInnerColor(Color255 _innerColor, bool _defaultFill = true)
	{
		innerColor = _innerColor;
		hoveredInnerColor = _innerColor;
		clickedInnerColor = _innerColor;
		selectedInnerColor = _innerColor;
		if (_defaultFill) {
			innerAnimation.current = innerColor;
			innerAlphaAnimation.current = (float)innerColor.a;
		}
		return true;
	}
	bool SetInnerColor(Color255 _innerColor, Color255 _hoveredColor, Color255 _clickedColor, Color255 _selectedColor, bool _defaultFill = true)
	{
		innerColor = _innerColor;
		hoveredInnerColor = _hoveredColor;
		clickedInnerColor = _clickedColor;
		selectedInnerColor = _selectedColor;
		if (_defaultFill) {
			innerAnimation.current = innerColor;
			innerAlphaAnimation.current = (float)innerColor.a;
		}
		return true;
	}
	// アウトラインを表示する際はtrueになっているかをチェック
	bool SetOutlineColor(Color255 _outerColor, float _outlineWidth, bool _defaultFill = true) {
		outerColor = _outerColor;
		hoveredOuterColor = _outerColor;
		clickedOuterColor = _outerColor;
		selectedOuterColor = _outerColor;
		outlineWidth = _outlineWidth;
		if (_defaultFill) {
			outerAnimation.current = outerColor;
			outerAlphaAnimation.current = (float)outerColor.a;
		}
		return true;
	}
	// アウトラインを表示する際はtrueになっているかをチェック
	bool SetOutlineColor(Color255 _outerColor, Color255 _hoveredColor, Color255 _clickedColor, Color255 _selectedColor, float _outlineWidth, bool _defaultFill = true) {
		outerColor = _outerColor;
		hoveredOuterColor = _hoveredColor;
		clickedOuterColor = _clickedColor;
		selectedOuterColor = _selectedColor;
		outlineWidth = _outlineWidth;
		if (_defaultFill) {
			outerAnimation.current = outerColor;
			outerAlphaAnimation.current = (float)outerColor.a;
		}
		return true;
	}

	// 更新描画
	void Collide() override;
	void Update() override;
	void Draw() override;

private:

	void CollideMouse();

private:
	TextObject textObject;

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

	int maxLength;
	bool cancelVaildFlag;
	bool singleCharOnlyFlag;
	bool numCharOnlyFlag;

	bool turnedOn;

	bool interruptMode;

	int inputHandle;
	std::string inputText;
};

