#pragma once
class ObjectBase
{
protected:
	ObjectBase(/* ���z�Ƃ��Ă͂����ɕ��荞�񂾂� */ float _x, float _y, float _sx, float _sy, int _innerColor, int _outerColor) {
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

	// �����ɎQ�Ɠn�����ꂽ��ʏ��Ȃǂ̍\���̂���ꂽ�������������H
};

