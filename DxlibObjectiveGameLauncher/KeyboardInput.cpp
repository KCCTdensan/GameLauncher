#include "KeyboardInput.h"

int Input::KeyboardInput::KEY[256];

void Input::KeyboardInput::Update()
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
