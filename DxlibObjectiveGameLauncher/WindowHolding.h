#pragma once
#include "MouseInput.h"
#include "ApplicationPreference.h"
#include <Windows.h>

class WindowHolding
{
public:
	static void Update();
	static void SwitchWindowMaximized() { windowMaximized = !windowMaximized; }
	static bool GetWindowMaximized() { return windowMaximized; }
private:
	static POINT po;
	static PosVec holdingWindowPos;

	static bool windowMaximized;

};

