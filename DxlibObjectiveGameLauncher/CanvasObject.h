#pragma once
#include "ObjectBase.h"
#include "MouseInput.h"
class CanvasObject :
	public ObjectBase
{
public:
	// 領域外は描画されない(子オブジェクトとして登録必要)
	CanvasObject(PosVec _pos, PosVec _size = PosVec()) :
		ObjectBase(_pos, _size), enabledFill(true), enabledOutline(false), outerColor(0), outlineWidth(0),
		enabledScrollX(false), enabledScrollY(false), scrollAmount(20.f), scrollBarWidth(15.f), canvasDrawingId(-1)
	{
		canvasId = MakeScreen((int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y, true);
		canvasOwner = true;
	}

	CanvasObject() :
		ObjectBase(PosVec(), PosVec()), enabledFill(true), enabledOutline(false), outerColor(0), outlineWidth(0),
		enabledScrollX(false), enabledScrollY(false), scrollAmount(20.f), scrollBarWidth(15.f), canvasDrawingId(-1) {}

	// 更新描画
	void Collide() override;
	void Update() override;
	void Draw() override;

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
		outlineWidth = _outlineWidth;
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

	// 面積指定
	void SetArea(PosVec area) {
		scrollDistance = area;
		if (scrollDistance.x > size.x) {
			enabledScrollX = true;
		}
		else if (scrollDistance.x <= size.x) {
			enabledScrollX = false;
		}
		scrollValue.x = 0.f;
		maskUpperLeft.x = (scrollDistance.x - size.x) * scrollValue.x;
		if (scrollDistance.y > size.y) {
			enabledScrollY = true;
		}
		else if (scrollDistance.y <= size.y) {
			enabledScrollY = false;
		}
		scrollValue.y = 0.f;
		maskUpperLeft.y = (scrollDistance.y - size.y) * scrollValue.y;
	}

	void SetScrollValue(PosVec _value) {
		scrollValue.x = _value.x;
		scrollValue.y = _value.y;
	}

	bool RegisterChildren(ObjectBase* _object) override;

private:

	void CollideMouse();

private:
	Color255 innerColor;
	Color255 outerColor;
	float outlineWidth;

	bool enabledFill;
	bool enabledOutline;

	bool enabledScrollX;
	bool enabledScrollY;
	float scrollAmount;
	PosVec maskUpperLeft; // sizeを足した値がLowerRight
	PosVec scrollDistance; 
	PosVec scrollValue; // each 0~1;
	float scrollBarWidth;

	int canvasDrawingId;
};

