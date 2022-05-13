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

	// ここに参照渡しされた画面情報などの構造体を入れた方がいいかも？
};

