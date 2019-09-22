#pragma once


namespace input
{
	enum KeyPressID
	{
		KeyPressZero,
		KeyPressOnce,
		KeyPressMuch
	};

	class Keyboard
	{
		KeyPressID keyPressStatus[256];

		void updateKeyPressStatus(int keyNo, char keyState);

	public:
		void update();
	};
}