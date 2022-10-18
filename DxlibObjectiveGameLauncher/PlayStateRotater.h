#pragma once
#include "PlayState.h"
class PlayStateRotater
{
public:
	PlayStateRotater();

	void Set(PlayState playState);
	void Rotate();
	PlayState GetNowState();

private:
	PlayState current;
};

