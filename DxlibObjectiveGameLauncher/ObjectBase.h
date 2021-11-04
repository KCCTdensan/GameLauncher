#pragma once
class ObjectBase
{
protected:
	ObjectBase(/* 理想としてはここに放り込んだり */ float _x, float _y, float _sx, float _sy, int _innerColor, int _outerColor) {
		x = _x;
		y = _y;
		sx = _sx;
		sy = _sy;
		innerColor = _innerColor;
		outerColor = _outerColor;
	};

	virtual void Update() = 0;
	virtual void Draw() = 0;

	float x, y, sx, sy;
	int innerColor;
	int outerColor;

	// ここに参照渡しされた画面情報などの構造体を入れた方がいいかも？
};

