#pragma once


namespace input
{
	class Keyboard
	{
		enum KeyPressID
		{
			KeyPressZero,
			KeyPressOnce,
			KeyPressMuch
		};

		KeyPressID keyPressStatus[256];

		void updateKeyPressStatus(int keyNo, char keyState);

	public:
		void update();
	};
}