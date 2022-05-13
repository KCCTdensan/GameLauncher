#pragma once
#include "PositionVector.h"

class ObjectBase
{
protected:
	ObjectBase(PosVec _pos, PosVec _size)
		:pos(_pos), size(_size) {}

	virtual void Update() = 0;
	virtual void Draw() = 0;

	PosVec pos;
	PosVec size;

	// �����ɎQ�Ɠn�����ꂽ��ʏ��Ȃǂ̍\���̂���ꂽ�������������H
};

