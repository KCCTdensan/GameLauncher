#include "ObjectOverlapping.h"

template<typename T> T* ObjectOverlapping<T>::object;
template bool ObjectOverlapping<ButtonObject>::UpdateObject(ButtonObject*);
template bool ObjectOverlapping<ButtonObject>::Reset();

template<typename T>
inline bool ObjectOverlapping<T>::UpdateObject(T* _object)
{
	if (object != nullptr && object != _object) {
		object->SetNoMouse();
	}
	object = _object;

	return true;
}