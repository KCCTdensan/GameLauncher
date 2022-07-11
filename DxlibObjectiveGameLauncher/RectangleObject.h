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

	// �F�L����������
	bool SetEnabledFill(bool _enabled) { enabledFill = _enabled; return true; }
	bool SetEnabledFill() { return enabledFill; }
	bool SetEnabledOutline(bool _enabled, float _outlineWidth = 1) { enabledOutline = _enabled; outlineWidth = (enabledOutline) ? _outlineWidth : 0; return true; }
	bool SetEnabledOutline() { return enabledOutline; }

	// �F���o�^��
	bool SetInnerColor(int _innerColor) { innerColor = _innerColor; return true; }
	bool SetOutlineColor(int _outerColor, float _outlineWidth) { outerColor = _outerColor; outlineWidth = _outlineWidth; return true; }

	// �X�V�`��
	void Collide();
	void Update();
	void Draw();

private:

	void CollideMouse();

private:
	int innerColor;

	int outerColor;
	float outlineWidth;

	bool enabledFill;
	bool enabledOutline;

	// �A�j���[�V�����ǉ��̏ꍇ�C�����o�C���\�b�h�ǉ�
	// �O���f�[�V�����̏ꍇ�����l

	/******************/

	int currentInnerColor;
};

