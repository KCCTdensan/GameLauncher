#include "ObjectBase.h"

bool ObjectBase::Move(PosVec _delta)
{
	pos = PosVec(pos.x + _delta.x, pos.y + _delta.y);

	// �q�v�f�ɂ��K�p
	for (int i = 0; i < children.size(); i++) {
		children[i]->Move(_delta);
	}
	return true;
}