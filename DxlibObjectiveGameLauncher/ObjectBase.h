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

	// マウス入力解除(Selectedなどの任意の分岐後に呼び出し等)
	bool SetMouseOff() { mouseClicked = false; mouseSelected = false; return true; }

	// マウス判定系取得
	bool GetMouseHit() { return mouseHit; }
	bool GetMouseClicked() { return mouseClicked; }
	bool GetMouseSelected() { return mouseSelected; }

	// ここに参照渡しされた画面情報などの構造体を入れた方がいいかも？
};

