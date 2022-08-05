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
		: ObjectBase(_pos, _size), enabledFill(_enabledFill), enabledOutline(_enabledOutline), innerColor(0), selectedColor(0), hoveredColor(0), clickedColor(0), outerColor(0), outlineWidth(0),
		currentInnerColor(0), animationStartColor(0), animationEndColor(0), animationDuraion(0.f), animationCurrentlyRate(0.f),
		animationEnabled(false), mRed(0.f), mGreen(0.f), mBlue(0.f), animationElapsedTime(0.f), animationDuraionRemain(0.f)
	{}

	ButtonObject()
		: ObjectBase(PosVec(), PosVec()), enabledFill(true), enabledOutline(false), innerColor(0), selectedColor(0), hoveredColor(0), clickedColor(0), outerColor(0), outlineWidth(0),
		currentInnerColor(0), animationStartColor(0), animationEndColor(0), animationDuraion(0.f), animationCurrentlyRate(0.f),
		animationEnabled(false), mRed(0.f), mGreen(0.f), mBlue(0.f), animationElapsedTime(0.f), animationDuraionRemain(0.f)
	{}

	// �F�L����������
	bool SetEnabledFill(bool _enabled) { enabledFill = _enabled; return true; }
	bool SetEnabledFill() { return enabledFill; }
	bool SetEnabledOutline(bool _enabled, float _outlineWidth = 1) { enabledOutline = _enabled; outlineWidth = (enabledOutline) ? _outlineWidth : 0; return true; }
	bool SetEnabledOutline() { return enabledOutline; }

	// �F���o�^��
	bool SetInnerColor(Color255 _innerColor, Color255 _hoveredColor, Color255 _clickedColor, Color255 _selectedColor, bool _defaultFill = true)
	{
		innerColor = _innerColor;
		hoveredColor = _hoveredColor;
		clickedColor = _clickedColor;
		selectedColor = _selectedColor;
		if (_defaultFill) currentInnerColor = innerColor;
		return true;
	}
	bool SetOutlineColor(Color255 _outerColor, float _outlineWidth) { outerColor = _outerColor; outlineWidth = _outlineWidth; return true; }

	// �A�j���[�V�����ݒ�
	bool SetAnimation(float _duration) { animationEnabled = true; animationDuraion = _duration; animationDuraionRemain = _duration; animationElapsedTime = 0.f; return true; }
	bool SetAnimation() { animationEnabled = false; return true; }

	// �X�V�`��
	void Collide();
	void Update();
	void Draw();

private:

	void CollideMouse();

	// �A�j���[�V�����ڕW
	void SetAnimationPoint(Color255 _start, Color255 _goal);

private:
	Color255 innerColor;
	Color255 hoveredColor;
	Color255 clickedColor;
	Color255 selectedColor;

	Color255 outerColor;
	float outlineWidth;

	bool enabledFill;
	bool enabledOutline;

	/******************/

	Color255 currentInnerColor;

	/******************/

	bool animationEnabled;

	Color255 animationStartColor;
	Color255 animationEndColor;
	float mRed;
	float mGreen;
	float mBlue;

	float animationDuraion;
	float animationDuraionRemain;
	float animationElapsedTime;
	float animationCurrentlyRate;
};

