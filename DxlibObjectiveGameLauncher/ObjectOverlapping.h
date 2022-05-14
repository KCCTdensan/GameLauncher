#pragma once
#include "ButtonObject.h"

template <typename T>
class ObjectOverlapping
{
public:
	static bool Reset() { delete(object); return true; }
	static bool UpdateObject(T* _object); // SetNoMouse() メソッドを持っている必要あり
	static T* GetObj() { return object; }

private:
	static T* object;
};

template<typename T> T* ObjectOverlapping<T>::object;

template<typename T>
inline bool ObjectOverlapping<T>::UpdateObject(T* _object)
{
	if (object != nullptr && object != _object) {
		object->SetNoMouse();
	}
	object = _object;

	return true;
}