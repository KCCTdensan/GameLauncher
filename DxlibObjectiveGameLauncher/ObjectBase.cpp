#include "ObjectBase.h"

bool ObjectBase::Move(PosVec _delta)
{
	pos = PosVec(pos.x + _delta.x, pos.y + _delta.y);

	// 子要素にも適用
	for (int i = 0; i < children.size(); i++) {
		children[i]->Move(_delta);
	}
	return true;
}