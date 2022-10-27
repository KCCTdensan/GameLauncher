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
	inline static const std::string analyticsJson = ".\\assets\\json\\analytics.json";

	inline static const std::string initializeGUID = "00000000-0000-0000-0000-000000000000";

	inline static const std::string musicCategoryName = "MUSIC";

	inline static constexpr float bannerHeight = 75.f;
	inline static constexpr float headerTabHeight = 50.f;
	inline static constexpr float startScenePos = bannerHeight + headerTabHeight;
	
	inline static const float returnTextIndent = 1.15f;

private:
	static PosVec backgroundSize;
};