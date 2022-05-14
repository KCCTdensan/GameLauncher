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
		: ObjectBase(_pos, _size), enabled(true), enabledFill(_enabledFill), enabledOutline(_enabledOutline), innerColor(0), selectedColor(0), hoveredColor(0), clickedColor(0), outerColor(0), outlineWidth(0),
		mouseHit(false), currentInnerColor(0), mouseClicked(false), mouseSelected(false)
	{}

	bool SetEnabled(bool _enabled) { enabled = _enabled; return true; }
	bool SetEnabled() { return enabled; }

	// 色有効化無効化
	bool SetEnabledFill(bool _enabled) { enabledFill = _enabled; return true; }
	bool SetEnabledFill() { return enabledFill; }
	bool SetEnabledOutline(bool _enabled, float _outlineWidth = 1) { enabledOutline = _enabled; outlineWidth = (enabledOutline) ? _outlineWidth : 0; return true; }
	bool SetEnabledOutline() { return enabledOutline; }

	// 色情報登録等
	bool SetInnerColor(int _innerColor, int _hoveredColor, int _clickedColor, int _selectedColor) { innerColor = _innerColor; hoveredColor = _hoveredColor; clickedColor = _clickedColor; selectedColor = _selectedColor; return true; }
	bool SetOutlineColor(int _outerColor, float _outlineWidth) { outerColor = _outerColor; outlineWidth = _outlineWidth; return true; }

	// 更新描画
	void Collide();
	void Update();
	void Draw();

	// 上にレイヤが重なっていた場合の解除処理
	bool SetNoMouse() { mouseHit = false; mouseClicked = false; return true; }

private:

	void CollideMouse();

private:
	bool enabled;

	int innerColor;
	int hoveredColor;
	int clickedColor;
	int selectedColor;

	int outerColor;
	float outlineWidth;

	bool enabledFill;
	bool enabledOutline;

	/******************/

	int currentInnerColor;
	bool mouseHit;
	bool mouseSelected;
	bool mouseClicked;
};

