#include "ApplicationBuilder.h"

ApplicationBuilder::ApplicationBuilder()
{
	tmp = ApplicationPreference::clientAssets + "\\fonts\\03スマートフォントUI.otf";
	// Fontを追加
	if (AddFontResourceEx(tmp.c_str(), FR_PRIVATE, NULL) <= 0) {
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
	tmp = ApplicationPreference::clientAssets + "\\fonts\\MPLUS2-Medium.ttf";
	// Fontを追加
	if (AddFontResourceEx(tmp.c_str(), FR_PRIVATE, NULL) <= 0) {
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

	ApplicationTime::Initialize();
}

ApplicationBuilder::~ApplicationBuilder()
{
	RemoveFontResourceEx(tmp.c_str(), FR_PRIVATE, NULL);
}

void ApplicationBuilder::Update()
{
	ApplicationTime::Update();
	WindowHolding::Update();
}
