#pragma once
#include "MouseInput.h"
class WindowHolding
{
public:
	static void Update();
private:
	static POINT po;
	static PosVec holdingWindowPos;

};

