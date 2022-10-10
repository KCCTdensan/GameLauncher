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
	inline static const std::string worksJson = ".\\assets\\json\\works.json";
	inline static const std::string setJson = ".\\assets\\json\\sets.json";

	inline static constexpr float bannerHeight = 75.f;
	inline static constexpr float headerTabHeight = 50.f;
	inline static constexpr float startScenePos = bannerHeight + headerTabHeight;
	
	inline static const float returnTextIndent = 1.15f;

private:
	static PosVec backgroundSize;
};