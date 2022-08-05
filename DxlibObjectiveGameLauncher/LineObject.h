#pragma once
#include "ObjectBase.h"
class LineObject :
	public ObjectBase
{
public:
	// pos1は始点,pos2は終点
	LineObject(PosVec _pos1, PosVec _pos2, bool _enabledOutline = true)
		: ObjectBase(_pos1, _pos2), enabledOutline(_enabledOutline), outerColor(0), outlineWidth(1.f) {}
	LineObject()
		: ObjectBase(PosVec(), PosVec()), enabledOutline(false), outerColor(0), outlineWidth(1.f) {}

	bool SetEnabledOutline(bool _enabled, float _outlineWidth = 1) { enabledOutline = _enabled; outlineWidth = (enabledOutline) ? _outlineWidth : 0; return true; }
	bool SetEnabledOutline() { return enabledOutline; }

	bool SetOutlineColor(Color255 _outerColor, float _outlineWidth) { outerColor = _outerColor; outlineWidth = _outlineWidth; return true; }

	// 更新描画
	void Collide();
	void Update();
	void Draw();

private:
	Color255 outerColor;
	float outlineWidth;

	bool enabledOutline;
};

