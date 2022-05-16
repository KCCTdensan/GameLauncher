#pragma once
#include "PositionVector.h"

class ApplicationPreference {
public:
	static PosVec GetBackgroundSize()
	{
		return backgroundSize;
	}

public:
	inline static constexpr int sceneHistories = 4;

private:
	static PosVec backgroundSize;
};