#pragma once
#include "DxLib.h"
#include "SceneManager.h"
#include "SceneSet.h"
#include "OriginalObjects.h"
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

	static void SetSubtitle(std::string subtitle);

private:
	static bool beInitialized;
	static std::vector<SceneSet> sceneSets;
	static std::vector<ButtonObject> navLinks;
	static RectangleObject banner;
	static LineObject headerLine;
	static std::vector<ButtonObject> systemButtons;
	static TextObject titleLogo;
	static TextObject subtitleLogo;

	static float height;
	static float navWidth;

	static void RegFonts();

	static std::vector<FontHandle> fonts;
};

