#pragma once
#include "DxLib.h"
#include "SceneManager.h"
#include "SceneSet.h"
#include "OriginalObjects.h"
#include "AppClose.h"
#include "WindowHolding.h"
#include "WindowHwnd.h"
#include "Header.h"
#include <array>
#include <vector>
/* ÉVÅ[Éìà⁄ìÆìoò^óp */
#include "DebugScene.h"
#include "HomeScene.h"

class Header
	: public SceneBase
{
public:

	Header();

	void Collide();
	void Update();
	void Draw();

	void SetSubtitle(std::string subtitle);

private:
	bool beInitialized;
	std::vector<SceneSet> sceneSets;
	std::vector<ButtonObject> navLinks;
	RectangleObject banner;
	LineObject headerLine;
	std::vector<ButtonObject> systemButtons;
	TextObject titleLogo;
	TextObject subtitleLogo;

	float height;
	float navWidth;

	void RegFonts();

	std::vector<FontHandle> fonts;
};

