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

	inline static const float bannerHeight = 75.f;
	inline static const float headerTabHeight = 50.f;
	inline static const float startScenePos = bannerHeight + headerTabHeight;
	
	inline static const float returnTextIndent = 1.15f;

private:
	static PosVec backgroundSize;
};