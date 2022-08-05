#pragma once
#include "DxLib.h"
#include "SceneManager.h"
#include "SceneSet.h"
#include "ButtonObject.h"
#include "RectangleObject.h"
#include "AppClose.h"
#include "WindowHolding.h"
#include "WindowHwnd.h"
#include <array>
#include <vector>
/* ÉVÅ[Éìà⁄ìÆìoò^óp */
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
	static RectangleObject banner;
	static std::vector<ButtonObject> systemButtons;

	static float height;
	static float navWidth;
};

