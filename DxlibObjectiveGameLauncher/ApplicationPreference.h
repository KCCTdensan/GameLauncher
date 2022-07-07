#pragma once
#include <string>
#include "PositionVector.h"

class ApplicationPreference {
public:
	static PosVec GetBackgroundSize()
	{
		return backgroundSize;
	}

public:
	inline static constexpr int sceneHistories = 4;
	inline static constexpr int headerButtonNum = 3;

	inline static const std::string clientAssets = "assets\\client";

private:
	static PosVec backgroundSize;
};