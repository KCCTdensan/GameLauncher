#pragma once
#include "ObjectBase.h"
#include "MouseInput.h"
#include "ButtonObject.h"
#include "ProgressObject.h"
#include <array>

class CanvasObject :
	public ObjectBase
{
public:
	// �̈�O�͕`�悳��Ȃ�(�q�I�u�W�F�N�g�Ƃ��ēo�^�K�v)
	CanvasObject(PosVec _pos, PosVec _size, bool _scrollVertical = true, bool _scrollAutoHiding = true, float _scrollObjectWidth = 20.f) :
		ObjectBase(_pos, _size), enabledFill(true), enabledOutline(false), outerColor(0), outlineWidth(0),
		enabledScrollX(false), enabledScrollY(false), scrollPercentage(0.f), scrollBarWidth(_scrollObjectWidth), canvasDrawingId(-1), scrollButtonSize(20.f),
		scrollVertical(_scrollVertical), scrollAutoHiding(_scrollAutoHiding)
	{
		canvasId = MakeScreen((int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y, true);
		canvasOwner = true;
		scrollButton[(int)DirectionType::LEFT] = ButtonObject(PosVec(pos.x, pos.y + _size.y - scrollBarWidth), PosVec(scrollBarWidth, scrollBarWidth), true, true);
		scrollButton[(int)DirectionType::RIGHT] = ButtonObject(PosVec(pos.x + _size.x - scrollBarWidth * 2.f, pos.y + _size.y - scrollBarWidth), PosVec(scrollBarWidth, scrollBarWidth), true, true);
		scrollButton[(int)DirectionType::TOP] = ButtonObject(PosVec(pos.x + _size.x - scrollBarWidth, pos.y), PosVec(scrollBarWidth, scrollBarWidth), true, true);
		scrollButton[(int)DirectionType::BOTTOM] = ButtonObject(PosVec(pos.x + _size.x - scrollBarWidth, pos.y + _size.y - scrollBarWidth), PosVec(scrollBarWidth, scrollBarWidth), true, true);
		for (auto& item : scrollButton) {
			ObjectBase::RegisterChildren(&item);
			item.SetInnerColor(Color255(255, 200), Color255(100, 200), Color255(190, 200), Color255(200, 200));
			item.SetOutlineColor(Color255(100, 200), .5f);
			item.SetEnforcedCollision(9);
		}
		// �c
		scrollBar[0] = ProgressObject(PosVec(pos.x + size.x - scrollBarWidth, pos.y + scrollBarWidth), PosVec(scrollBarWidth, size.y - scrollBarWidth * 2.f), true, 0.f);
		scrollBar[1] = ProgressObject(PosVec(pos.x + scrollBarWidth, pos.y + size.y - scrollBarWidth), PosVec(size.x - scrollBarWidth * 3.f, scrollBarWidth), false, 0.f);
	
		for (auto& item : scrollBar) {
			ObjectBase::RegisterChildren(&item);
			item.SetInnerColor(Color255(255, 30), Color255(230, 200), Color255(230, 200), Color255(230, 200));
			item.GetSlider()->SetInnerColor(Color255(200, 200));
			item.SetInnerAnimation(.1f);
			item.SetEnforcedCollision(10);
			// ��O�΍�
			item.SetupSlider();
		}
	}

	CanvasObject() :
		ObjectBase(PosVec(), PosVec()), enabledFill(true), enabledOutline(false), outerColor(0), outlineWidth(0), scrollVertical(true), scrollAutoHiding(false),
		enabledScrollX(false), enabledScrollY(false), scrollPercentage(20.f), scrollBarWidth(20.f), canvasDrawingId(-1), scrollButtonSize(20.f) {}


	~CanvasObject() 
	{
		DeleteGraph(canvasId);
	}

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
	void SetArea(PosVec area, float _scrollPercentage = 0.15f) {
		scrollDistance = area;
		scrollPercentage = _scrollPercentage;
		if (scrollDistance.x > size.x) {
			enabledScrollX = true;
		}
		else if (scrollDistance.x <= size.x) {
			enabledScrollX = false;
			scrollDistance.x = size.x;
			scrollBar[1].SetEnabled(false);
			scrollButton[(int)DirectionType::LEFT].SetEnabled(false);
			scrollButton[(int)DirectionType::RIGHT].SetEnabled(false);
		}
		scrollValue.x = 0.f;
		maskUpperLeft.x = (scrollDistance.x - size.x) * scrollValue.x;
		if (scrollDistance.y > size.y) {
			enabledScrollY = true;
		}
		else if (scrollDistance.y <= size.y) {
			enabledScrollY = false;
			scrollDistance.y = size.y;
			scrollBar[0].SetEnabled(false);
			scrollButton[(int)DirectionType::TOP].SetEnabled(false);
			scrollButton[(int)DirectionType::BOTTOM].SetEnabled(false);
		}
		scrollValue.y = 0.f;
		maskUpperLeft.y = (scrollDistance.y - size.y) * scrollValue.y;
	}

	void SetScrollValue(PosVec _value) {
		scrollValue.x = _value.x;
		scrollValue.y = _value.y;
	}

	bool RegisterChildren(ObjectBase* _object) override;
	bool RegisterCanvas(ObjectBase* _object);

private:

	void CollideMouse() override;

private:
	Color255 innerColor;
	Color255 outerColor;
	float outlineWidth;

	bool enabledFill;
	bool enabledOutline;

	bool enabledScrollX;
	bool enabledScrollY;
	float scrollPercentage;
	PosVec maskUpperLeft; // size�𑫂����l��LowerRight
	PosVec scrollDistance;
	PosVec scrollValue; // each 0~1;
	float scrollBarWidth;

	int canvasDrawingId;

	std::array<ButtonObject, 4> scrollButton;
	std::array<ProgressObject, 2> scrollBar;
	float scrollButtonSize;

	bool scrollVertical;
	bool scrollAutoHiding;
};

