#pragma once
#include "DxLib.h"
#include "SceneManager.h"
#include "SceneSet.h"
#include "ButtonObject.h"
#include "RectangleObject.h"
#include <array>
#include <vector>
/* ƒV[ƒ“ˆÚ“®“o˜^—p */
#include "DebugScene.h"
#include "HomeScene.h"

class Header
{
public:

	static void Initialize();

	static void Collide();
	static void Update();
	static void Draw();

private:
	static bool beInitialized;
	static std::vector<SceneSet> sceneSets;
	static std::vector<ButtonObject> navLinks;

	static float height;
	static float navWidth;
};

