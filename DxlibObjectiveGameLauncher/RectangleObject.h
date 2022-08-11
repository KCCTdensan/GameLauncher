#pragma once
#include "ObjectBase.h"
#include "DxLib.h"
#include "MouseInput.h"
#include "ObjectOverlapping.h"

class RectangleObject :
	public ObjectBase
{
public:
	RectangleObject(PosVec _pos, PosVec _size, bool _enabledFill = true, bool _enabledOutline = false)
		: ObjectBase(_pos, _size), enabledFill(_enabledFill), enabledOutline(_enabledOutline), innerColor(0), outerColor(0), outlineWidth(0), currentInnerColor(0) {}

	RectangleObject()
		: ObjectBase(PosVec(), PosVec()), enabledFill(true), enabledOutline(false), innerColor(0), outerColor(0), outlineWidth(0), currentInnerColor(0) {}

	// 色有効化無効化
	bool SetEnabledFill(bool _enabled) { enabledFill = _enabled; return true; }
	bool SetEnabledFill() { return enabledFill; }
	bool SetEnabledOutline(bool _enabled, float _outlineWidth = 1) { enabledOutline = _enabled; outlineWidth = (enabledOutline) ? _outlineWidth : 0; return true; }
	bool SetEnabledOutline() { return enabledOutline; }

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
	// アウトラインを表示する際はtrueになっているかをチェック
	bool SetOutlineColor(Color255 _outerColor, float _outlineWidth, bool _defaultFill = true) {
		outerColor = _outerColor;
		if (_defaultFill) {
			outerAnimation.current = outerColor;
			outerAlphaAnimation.current = (float)outerColor.a;
		}
		return true;
	}

	Color255* GetColor(ColorType type) {
		switch (type)
		{
		case ColorType::INNER:
			return &innerColor;
		case ColorType::OUTER_INNER:
			return &outerColor;
		default:
			return nullptr;
		}
	}

	// 更新描画
	void Collide();
	void Update();
	void Draw();

private:

	void CollideMouse();

private:
	Color255 innerColor;

	Color255 outerColor;
	float outlineWidth;

	bool enabledFill;
	bool enabledOutline;

	// アニメーション追加の場合，メンバ，メソッド追加
	// グラデーションの場合も同様

	/******************/

	Color255 currentInnerColor;
};

