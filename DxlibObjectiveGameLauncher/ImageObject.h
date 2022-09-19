#pragma once
#include "ObjectBase.h"
class ImageObject :
	public ObjectBase
{
public:
	ImageObject(PosVec _pos, PosVec _size, int _imgHandle, bool _enabledFill = true, bool _enabledOutline = false)
		: ObjectBase(_pos, _size),
		enabledFill(_enabledFill), enabledOutline(_enabledOutline), innerColor(Color255(0, 0)), outerColor(Color255(0, 0)), outlineWidth(0)
	{
		SetImageHandle(_imgHandle);
	}

	ImageObject()
		: ObjectBase(PosVec(), PosVec()),
		enabledFill(true), enabledOutline(false), innerColor(Color255(0, 0)), outerColor(Color255(0, 0)), outlineWidth(0)
	{

	}

	// �F�L����������
	bool SetEnabledFill(bool _enabled) { enabledFill = _enabled; return true; }
	bool SetEnabledFill() { return enabledFill; }
	bool SetEnabledOutline(bool _enabled, float _outlineWidth = -1.f) { enabledOutline = _enabled; outlineWidth = _outlineWidth ? _outlineWidth <= 0.f : 0.f; return true; }
	// ����p���^�[��
	bool SetEnabledOutline() { return enabledOutline; }

	// �F���o�^��
	bool SetInnerColor(Color255 _innerColor, bool _defaultFill = true)
	{
		innerColor = _innerColor;
		if (_defaultFill) {
			innerAnimation.current = innerColor;
			innerAlphaAnimation.current = (float)innerColor.a;
		}
		disabledInnerColor = Color255(innerColor.r, innerColor.g, innerColor.b, (int)(innerColor.a / 5));
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
		disabledOuterColor = Color255(outerColor.r, outerColor.g, outerColor.b, (int)(outerColor.a / 5));
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

	// �X�V�`��
	void Collide() override;
	void Update() override;
	void Draw() override;

private:

	void CollideMouse() override {}

private:
	Color255 innerColor;
	Color255 outerColor;

	Color255 disabledInnerColor;
	Color255 disabledOuterColor;

	float outlineWidth;

	bool enabledFill;
	bool enabledOutline;
};

