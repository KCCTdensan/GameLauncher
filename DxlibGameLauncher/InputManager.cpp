#include "InputManager.h"
#include "DxLib.h"
#include "OperationData.h"


using namespace Input;

int KeyBoard::KEY[256];
int Mouse::MOUSE_X = 0, Mouse::MOUSE_Y = 0, Mouse::MOUSE_CLICK = 0;
int Mouse::MOUSE_WIN_X = 0, Mouse::MOUSE_WIN_Y = 0;
int Mouse::MOUSE_LEFT = 0;

KeyBoard::KeyBoard()
{
}


KeyBoard::~KeyBoard()
{
}

void KeyBoard::Update()
{
	static char buf[256];
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++) {
		if (buf[i]) {
			if (KEY[i] == 0) KEY[i] = 1;
			else if (KEY[i] >= 1) KEY[i] = 2;
		}
		else KEY[i] = 0;
	}
}


Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::Update()
{
	GetMousePoint(&MOUSE_X, &MOUSE_Y);
	MOUSE_WIN_X = static_cast<int>(MOUSE_X * Ope::WINDOW_SIZE_RATE_TIME);
	MOUSE_WIN_Y = static_cast<int>(MOUSE_Y * Ope::WINDOW_SIZE_RATE_TIME);
	MOUSE_CLICK = GetMouseInput();
	if ((MOUSE_CLICK & MOUSE_INPUT_LEFT) != 0)
	{
		if (MOUSE_LEFT >= MOUSE_LEFT_PRESS_FIRST) {
			MOUSE_LEFT = MOUSE_LEFT_PRESS_MUCH;
		}
		else {
			MOUSE_LEFT = MOUSE_LEFT_PRESS_FIRST;
		}
	}
	else {
		MOUSE_LEFT = MOUSE_LEFT_PRESS_ZERO;
	}
}
