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

	// ‚±‚±‚ÉQÆ“n‚µ‚³‚ê‚½‰æ–Êî•ñ‚È‚Ç‚Ì\‘¢‘Ì‚ğ“ü‚ê‚½•û‚ª‚¢‚¢‚©‚àH
};

