#pragma once
#include "MouseInput.h"
#include "ApplicationPreference.h"

class WindowHolding
{
public:
	static void Update();
private:
	static POINT po;
	static PosVec holdingWindowPos;

};

