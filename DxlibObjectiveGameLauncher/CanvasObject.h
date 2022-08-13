#pragma once
#include "ObjectBase.h"
#include "MouseInput.h"
#include "ButtonObject.h"
#include <array>

class CanvasObject :
	public ObjectBase
{
public:
	// �̈�O�͕`�悳��Ȃ�(�q�I�u�W�F�N�g�Ƃ��ēo�^�K�v)
	CanvasObject(PosVec _pos, PosVec _size = PosVec()) :
		ObjectBase(_pos, _size), enabledFill(true), enabledOutline(false), outerColor(0), outlineWidth(0),
		enabledScrollX(false), enabledScrollY(false), scrollAmount(20.f), scrollBarWidth(15.f), canvasDrawingId(-1), scrollButtonSize(20.f)
	{
		canvasId = MakeScreen((int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y, true);
		canvasOwner = true;
		scrollButton[(int)DirectionType::LEFT] = ButtonObject(PosVec(pos.x, pos.y + _size.y - 20.f), PosVec(20.f, 20.f), true, true);
		scrollButton[(int)DirectionType::RIGHT] = ButtonObject(PosVec(pos.x + _size.x - 40.f, pos.y + _size.y - 20.f), PosVec(20.f, 20.f), true, true);
		scrollButton[(int)DirectionType::TOP] = ButtonObject(PosVec(pos.x + _size.x - 20.f, pos.y), PosVec(20.f, 20.f), true, true);
		scrollButton[(int)DirectionType::BOTTOM] = ButtonObject(PosVec(pos.x + _size.x - 20.f, pos.y + _size.y - 20.f), PosVec(20.f, 20.f), true, true);
		for (auto& item : scrollButton) {
			ObjectBase::RegisterChildren(&item);
			item.SetInnerColor(Color255(255, 200), Color255(100, 200), Color255(190, 200), Color255(200, 200));
			item.SetOutlineColor(Color255(100, 200), .5f);
			item.SetEnforcedCollision(true);
		}
	}

	CanvasObject() :
		ObjectBase(PosVec(), PosVec()), enabledFill(true), enabledOutline(false), outerColor(0), outlineWidth(0),
		enabledScrollX(false), enabledScrollY(false), scrollAmount(20.f), scrollBarWidth(15.f), canvasDrawingId(-1), scrollButtonSize(20.f) {}

	// �X�V�`��
	void Collide() override;
	void Update() override;
	void Draw() override;

	// �F�L����������
	bool SetEnabledFill(bool _enabled) { enabledFill = _enabled; return true; }
	bool SetEnabledFill() { return enabledFill; }
	bool SetEnabledOutline(bool _enabled, float _outlineWidth = 1) { enabledOutline = _enabled; outlineWidth = (enabledOutline) ? _outlineWidth : 0; return true; }
	bool SetEnabledOutline() { return enabledOutline; }

	// �F���o�^��
	bool SetInnerColor(Color255 _innerColor, bool _defaultFill = true)
	{
		innerColor = _innerColor;
		if (_defaultFill) {
			innerAnimation.current = innerColor;
			innerAlphaAnimation.current = (float)innerColor.a;
		}
		return true;
	}

	// �A�E�g���C����\������ۂ�true�ɂȂ��Ă��邩���`�F�b�N
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

	// �ʐώw��
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
	PosVec maskUpperLeft; // size�𑫂����l��LowerRight
	PosVec scrollDistance;
	PosVec scrollValue; // each 0~1;
	float scrollBarWidth;

	int canvasDrawingId;

	std::array<ButtonObject, 4> scrollButton;
	float scrollButtonSize;
	
};

