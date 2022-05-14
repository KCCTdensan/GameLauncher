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
	// 上にレイヤが重なっていた場合の解除処理
	bool SetNoMouse() { mouseHit = false; mouseClicked = false; return true; }

	// ここに参照渡しされた画面情報などの構造体を入れた方がいいかも？
};

