#pragma once
#include "ButtonObject.h"

template <typename T>
class ObjectOverlapping
{
public:
	static bool Reset() { objectPrevious = object; object = nullptr; return true; }
	static bool UpdateObject(T* _object); // SetNoMouse() メソッドを持っている必要あり
	static T* GetObj() { return object; }

private:
	static T* object;
	static T* objectPrevious;
};

template<typename T> T* ObjectOverlapping<T>::object = nullptr;
template<typename T> T* ObjectOverlapping<T>::objectPrevious = nullptr;

template<typename T>
inline bool ObjectOverlapping<T>::UpdateObject(T* _object)
{
	if (objectPrevious == nullptr) OutputDebugString("!");
	if (object != nullptr && object != _object) {
		if (objectPrevious != _object)
			object->SetNoMouseWithClick();
		else 
			object->SetNoMouse();
	}
	object = _object;

	return true;
}