#include "keyboard.hpp"
#include <DxLib.h>


namespace input
{
	void Keyboard::updateKeyPressStatus(int keyNo, char keyState)
	{
		if(keyNo < 0 || keyNo >= 256)
		{
			return;
		}
		if(keyState == 0)
		{
			keyPressStatus[keyNo] = KeyPressZero;
			return;
		}
		switch(keyPressStatus[keyNo])
		{
		case KeyPressZero:
			keyPressStatus[keyNo] = KeyPressOnce;
			break;

		case KeyPressOnce:
			keyPressStatus[keyNo] = KeyPressMuch;
			break;
		}
	}

	void Keyboard::update()
	{
		char buffer[256];
		GetHitKeyStateAll(buffer);
		for(int i = 0; i < 256; ++i)
		{
			updateKeyPressStatus(i, buffer[i]);
		}
	}
}