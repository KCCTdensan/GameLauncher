#include "ObjectOverlapping.h"
#include "ObjectBase.h"


ObjectBase* ObjectOverlapping::object = nullptr;
ObjectBase* ObjectOverlapping::canvas = nullptr;
int ObjectOverlapping::enforcementedNum = 0;


bool ObjectOverlapping::UpdateObject(ObjectBase* _object, int enforcemented)
{
	if (enforcementedNum > enforcemented) return false;
	enforcementedNum = enforcemented;
	if (object != nullptr)
		object->SetNoMouseWithClick();
	object = _object;
	return true;
}

bool ObjectOverlapping::UpdateObjectForCanvas(ObjectBase* _canvas, int enforcemented)
{
	if (canvas != nullptr)
		canvas->SetNoMouseWithClick();
	canvas = _canvas;
	return true;
}
