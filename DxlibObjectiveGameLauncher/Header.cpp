#include "Header.h"

Header::Header()
	: beInitialized(false), navWidth(ApplicationPreference::GetBackgroundSize().x - 300), height(ApplicationPreference::headerTabHeight)
{
	if (beInitialized) return;

	SharingScenes ss(this);

	sceneSets = {
	SceneSet("debug", new DebugScene(SceneManager::GetSharingScenes())),
	SceneSet("home", new HomeScene(SceneManager::GetSharingScenes())),
	SceneSet("home", new HomeScene(SceneManager::GetSharingScenes()))
	};

	banner = RectangleObject(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::bannerHeight));
	banner.SetInnerColor(Color255("#dafcf5"));

	for (int i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		navLinks.push_back(ButtonObject(PosVec(ApplicationPreference::GetBackgroundSize().x - (navWidth / ApplicationPreference::headerButtonNum * (ApplicationPreference::headerButtonNum - i)), ApplicationPreference::bannerHeight),
			PosVec(navWidth / ApplicationPreference::headerButtonNum, height), true, true));
		navLinks[i].SetInnerColor(Color255("#b0f7ea"), Color255("#98d5ca"), Color255("#80b4ab"), Color255("#a4e6da"));
		navLinks[i].SetOutlineColor(
			Color255(150, 50),
			Color255(0xFF, 0x77, 0xFE),
			Color255(0xFF, 0x77, 0xFE),
			Color255(0xFF, 0x77, 0xFE), 2.f);
		navLinks[i].SetInnerAnimation(.2f);
		navLinks[i].SetOuterAnimation(0);
	}

	for (int i = 0; i < 3; i++) {
		systemButtons.push_back(ButtonObject(
			PosVec(
				ApplicationPreference::GetBackgroundSize().x - 60.f - 60.f * i,
				0.f),
			PosVec(60.f, 40.f), true, true));
		if (i == 0)
			systemButtons[i].SetInnerColor(Color255("#dafcf5"), Color255("#b0393a"), Color255("#812a2b"), Color255("#bb3c3d"));
		else
			systemButtons[i].SetInnerColor(Color255("#dafcf5"), Color255("#96aea9"), Color255("#7a8d89"), Color255("#aec9c3"));
		systemButtons[i].SetOutlineColor(Color255(120), 1.f);
	}

	headerLine = LineObject(
		PosVec(0.f, ApplicationPreference::bannerHeight),
		PosVec(
			ApplicationPreference::GetBackgroundSize().x,
			ApplicationPreference::bannerHeight)
	);
	headerLine.SetEnabledOutline(true);
	headerLine.SetOutlineColor(Color255(0xFF, 0x77, 0xFE), 2.5f);

	titleLogo = TextObject(PosVec(7.f, 7.f), PosVec(), "mplus60", "Game Launcher", Color255(), TextAlign::LEFT, false);
	subtitleLogo = TextObject(PosVec(), PosVec(), "mplus25", "Sample Text", Color255(), TextAlign::LEFT, false);

	titleLogo.SetInnerColor(Color255("#88bcb1"));
	subtitleLogo.SetInnerColor(Color255("#88bcb1"));

	beInitialized = true;

	// フォント追加
	fonts.push_back(FontHandle("mplus60", "M PLUS 2", 60, 100));
	fonts.push_back(FontHandle("mplus25", "M PLUS 2", 40, 100));
}

void Header::Collide()
{
	banner.Collide();
	for (int i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		navLinks[i].Collide();
	}
	for (int i = 0; i < 3; i++) {
		systemButtons[i].Collide();
	}
}

void Header::Update()
{
	RegFonts();

	banner.Update();
	for (int i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		navLinks[i].Update();

		if (navLinks[i].GetMouseSelected()) {
			navLinks[i].SetMouseOff();
			SceneManager::ChangeScene(sceneSets[i].sceneName, sceneSets[i].scene, false);
			//SceneManager::ChangeScene(sceneSets[i].sceneName, new DebugScene(), false);
		}
	}
	for (int i = 0; i < 3; i++) {
		systemButtons[i].Update();
	}
	if (systemButtons[0].GetMouseSelected()) {
		WindowHwnd::WindowClose(GetMainWindowHandle());
		systemButtons[0].SetMouseOff();
	}
	if (systemButtons[1].GetMouseSelected()) {
		if (!WindowHolding::GetWindowMaximized()) {
			WindowHwnd::WindowMaximize(GetMainWindowHandle());
		}
		else
		{
			WindowHwnd::WindowNormalize(GetMainWindowHandle());
		}
		systemButtons[1].SetMouseOff();
	}
	if (systemButtons[2].GetMouseSelected()) {
		WindowHwnd::WindowMinimize(GetMainWindowHandle());
		systemButtons[2].SetMouseOff();
	}
	if (subtitleLogo.GetPos().x != (int)titleLogo.GetTextWidth() + 40.f) {
		subtitleLogo.SetPos(PosVec((int)titleLogo.GetTextWidth() + 40.f, 27.f));
		subtitleLogo.CalcPos();
	}
	titleLogo.Update();
	subtitleLogo.Update();

	std::string titleName = titleLogo.GetText() + " : " + subtitleLogo.GetText();

	SetMainWindowText(titleName.c_str()); // アプリのタイトル名の変更
}

void Header::Draw()
{
	banner.Draw();
	for (int i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		navLinks[i].Draw();
	}
	for (int i = 0; i < 3; i++) {
		systemButtons[i].Draw();
	}
	headerLine.Draw();
	titleLogo.Draw();
	subtitleLogo.Draw();
	//DrawBoxAA(0, 0, 1920, 1080, GetColor(255, 255, 255), false, 2.); // debug
}

void Header::SetSubtitle(std::string subtitle)
{
	if (subtitleLogo.GetText() == subtitle) return;
	subtitleLogo.SetText(subtitle);
}
