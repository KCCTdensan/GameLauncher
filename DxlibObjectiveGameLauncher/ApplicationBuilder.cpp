#include "ApplicationBuilder.h"

ApplicationBuilder::ApplicationBuilder()
{
	tmp = ApplicationPreference::clientAssets + "\\fonts\\03スマートフォントUI.otf";
	// Fontを追加
	if (AddFontResourceEx(tmp.c_str(), FR_PRIVATE, NULL) <= 0) {
		MessageBox(GetMainWindowHandle(), "フォント読込失敗", "", MB_OK);
	}
	tmp = ApplicationPreference::clientAssets + "\\fonts\\MPLUS2-Medium.ttf";
	// Fontを追加
	if (AddFontResourceEx(tmp.c_str(), FR_PRIVATE, NULL) <= 0) {
		MessageBox(GetMainWindowHandle(), "フォント読込失敗", "", MB_OK);
	}

	/*SetKeyInputStringColor(
		Color255("#000000").Get(),
		Color255("#000000").Get(),
		Color255("#FFFFFF").Get(),
		Color255("#FFFFFF").Get(),
		Color255("#FFFFFF").Get(),
		Color255("#000000").Get(),
		Color255("#FFFFFF").Get());*/

	SetKeyInputCursorBrinkFlag(TRUE);
	SetKeyInputCursorBrinkTime(500);

	setlocale(LC_ALL, "Japanese_Japan.932");


	ApplicationTime::Initialize();

	SetWindowLong(GetMainWindowHandle(), GWL_EXSTYLE, WS_EX_TOOLWINDOW);

	RequiredFileChecker requiredFileChecker;
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
