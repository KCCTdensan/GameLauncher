#pragma once
#include "PositionVector.h"

class ApplicationPreference {
public:
	static PosVec GetBackgroundSize()
	{
		return backgroundSize;
	}

private:
	static PosVec backgroundSize;
};

PosVec ApplicationPreference::backgroundSize = PosVec(1920, 1080);