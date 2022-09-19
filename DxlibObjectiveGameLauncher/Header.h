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
/* シーン移動登録用 */
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
	std::vector<ButtonObject> arrowButtons;
	TextObject titleLogo;
	TextObject subtitleLogo;

	float height;
	float navWidth;

};

