#pragma once
#include "ApplicationPreference.h"
#include "lib/picojson.h"
#include "DxLib.h"
#include <fstream>
#include <cassert>
#include <iostream> // std::cout
#include <sstream>
#include <numbers>
#include "ExePath.h"
#include <direct.h>
#include <sys/stat.h>

class RequiredFileChecker
{
public:
	RequiredFileChecker();

private:
	void CheckAssetsJson();
	void CheckWorksJson();
	void CheckAnalyticsJson();
};

