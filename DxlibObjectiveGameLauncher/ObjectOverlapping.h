#pragma once

class ObjectBase;

class ObjectOverlapping
{
public:
	static bool Reset() {
		enforcementedNum = 0;
		object = nullptr;
		canvas = nullptr;
		return true;
	}
	static bool UpdateObject(ObjectBase* _object, int enforcemented = 1); // SetNoMouse() メソッドを持っている必要あり
	static bool UpdateObjectForCanvas(ObjectBase* _canvas, int enforcemented = 1); // SetNoMouse() メソッドを持っている必要あり

private:
	static int enforcementedNum;
	static ObjectBase* object;
	static ObjectBase* canvas;
};
