#pragma once
#include "PositionVector.h"

class ObjectBase
{
protected:
	ObjectBase(PosVec _pos, PosVec _size)
		:pos(_pos), size(_size), mouseHit(false), mouseClicked(false), mouseSelected(false) {}

	virtual void Update() = 0;
	virtual void Draw() = 0;

	PosVec pos;
	PosVec size;

	bool mouseHit;
	bool mouseSelected;
	bool mouseClicked;

public:
	// ��Ƀ��C�����d�Ȃ��Ă����ꍇ�̉�������
	bool SetNoMouse() { mouseHit = false; mouseClicked = false; return true; }

	// �����ɎQ�Ɠn�����ꂽ��ʏ��Ȃǂ̍\���̂���ꂽ�������������H
};

