#pragma once
#include "ObjectBase.h"
#include "DxLib.h"
class RectangleObject :
	public ObjectBase
{
public:
	RectangleObject(PosVec _pos, PosVec _size, bool _enabledFill = true, bool _enabledOutline = false)
		: ObjectBase(_pos, _size), enabled(true), enabledFill(_enabledFill), enabledOutline(_enabledOutline), innerColor(0), outerColor(0), outlineWidth(0), currentInnerColor(0) {}

	bool SetEnabled(bool _enabled) { enabled = _enabled; return true; }
	bool SetEnabled() { return enabled; }

	// 色有効化無効化
	bool SetEnabledFill(bool _enabled) { enabledFill = _enabled; return true; }
	bool SetEnabledFill() { return enabledFill; }
	bool SetEnabledOutline(bool _enabled, float _outlineWidth = 1) { enabledOutline = _enabled; outlineWidth = (enabledOutline) ? _outlineWidth : 0; return true; }
	bool SetEnabledOutline() { return enabledOutline; }

	// 色情報登録等
	bool SetInnerColor(int _innerColor) { innerColor = _innerColor; return true; }
	bool SetOutlineColor(int _outerColor, float _outlineWidth) { outerColor = _outerColor; outlineWidth = _outlineWidth; return true; }

	// 更新描画
	void Collide() {};
	void Update();
	void Draw();

private:
	bool enabled;

	int innerColor;

	int outerColor;
	float outlineWidth;

	bool enabledFill;
	bool enabledOutline;

	// アニメーション追加の場合，メンバ，メソッド追加
	// グラデーションの場合も同様

	/******************/

	int currentInnerColor;
};

