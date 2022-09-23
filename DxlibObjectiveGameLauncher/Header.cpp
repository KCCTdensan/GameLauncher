#include "Header.h"

Header::Header()
	: beInitialized(false), navWidth(ApplicationPreference::GetBackgroundSize().x - 300), height(ApplicationPreference::headerTabHeight),
	banner(nullptr), headerLine(nullptr), subtitleLogo(nullptr), titleLogo(nullptr)
{
	if (beInitialized) return;
	int i = 0;
	sceneSets = {
	SceneSet("Welcome", new WelcomeScene(SceneManager::GetSharingScenes())),
	SceneSet("Home", new HomeScene(SceneManager::GetSharingScenes())),
	SceneSet("Debug", new DebugScene(SceneManager::GetSharingScenes()))
	};

	banner = new RectangleObject(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::bannerHeight));
	banner->SetInnerColor(ColorPreset::headerBanner);

	for (i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		navLinks.push_back(new ButtonObject(PosVec(ApplicationPreference::GetBackgroundSize().x - (navWidth / ApplicationPreference::headerButtonNum * (ApplicationPreference::headerButtonNum - i)), ApplicationPreference::bannerHeight),
			PosVec(navWidth / ApplicationPreference::headerButtonNum, height), true, true));
		navLinks[i]->SetInnerColor(ColorPreset::navLinksInner, ColorPreset::navLinksHovered, ColorPreset::navLinksClicked, ColorPreset::navLinksSelected);
		navLinks[i]->SetOutlineColor(
			ColorPreset::navLinksOuter,
			ColorPreset::navLinksOuterMouse,
			ColorPreset::navLinksOuterMouse,
			ColorPreset::navLinksOuterMouse, 2.f);
		navLinks[i]->SetInnerAnimation(.1f);
		navLinks[i]->SetOuterAnimation(0);
	}

	/*navLinks[0].SetupText("mplus25", "Debug", ColorPreset::titleLogo);
	navLinks[1].SetupText("mplus25", "Home", ColorPreset::titleLogo);
	navLinks[2].SetupText("mplus25", "Home", ColorPreset::titleLogo);*/

	for (i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		navLinks[i]->SetupText("mplus25", sceneSets[i].sceneName, ColorPreset::titleLogo);
		navLinks[i]->GetTextObject()->Move(PosVec(7.f, 7.f));
	}

	arrowButtons.resize(2, nullptr);
	i = 0;
	for (auto& item : arrowButtons) {
		item = new ButtonObject(PosVec(), PosVec(), true, true);
		item->SetPos(PosVec((ApplicationPreference::GetBackgroundSize().x - navWidth) / 4.f + (float)i * ((ApplicationPreference::GetBackgroundSize().x - navWidth) / 4.f), ApplicationPreference::bannerHeight));
		item->SetSize(PosVec((ApplicationPreference::GetBackgroundSize().x - navWidth) / 4.f, ApplicationPreference::headerTabHeight));
		item->SetInnerColor(ColorPreset::navLinksInner, ColorPreset::navLinksHovered, ColorPreset::navLinksClicked, ColorPreset::navLinksSelected);
		item->SetOutlineColor(
			ColorPreset::navLinksOuter,
			ColorPreset::navLinksOuterMouse,
			ColorPreset::navLinksOuterMouse,
			ColorPreset::navLinksOuterMouse, 2.f);
		item->SetInnerAnimation(.1f);
		item->SetOuterAnimation(0);
		i++;
	}
	arrowButtons[0]->SetupText("mplus25", "←", ColorPreset::titleLogo);
	arrowButtons[1]->SetupText("mplus25", "→", ColorPreset::titleLogo);

	for (auto& item : arrowButtons)
		item->GetTextObject()->Move(PosVec(15.f, 7.f));

	for (i = 0; i < 3; i++) {
		systemButtons.push_back(new ButtonObject(
			PosVec(
				ApplicationPreference::GetBackgroundSize().x - 60.f - 60.f * i,
				0.f),
			PosVec(60.f, 40.f), true, true));
		if (i == 0)
			systemButtons[i]->SetInnerColor(ColorPreset::systemButtonInner, ColorPreset::systemButtonHovered, ColorPreset::systemButtonClicked, ColorPreset::systemButtonSelected);
		else
			systemButtons[i]->SetInnerColor(ColorPreset::systemButtonInner, ColorPreset::systemButtonHoveredOnClose, ColorPreset::systemButtonClickedOnClose, ColorPreset::systemButtonSelectedOnClose);
		systemButtons[i]->SetOutlineColor(Color255(120), 1.f);
	}

	headerLine = new LineObject(
		PosVec(0.f, ApplicationPreference::bannerHeight),
		PosVec(
			ApplicationPreference::GetBackgroundSize().x,
			ApplicationPreference::bannerHeight)
	);
	headerLine->SetEnabledOutline(true);
	headerLine->SetOutlineColor(Color255(0xFF, 0x77, 0xFE), 2.5f);

	titleLogo = new TextObject(PosVec(7.f, 7.f), PosVec(), "smart60", "Game Launcher", Color255(), TextAlign::LEFT, false);
	subtitleLogo = new TextObject(PosVec(), PosVec(), "mplus25", "Sample Text", Color255(), TextAlign::LEFT, false);

	titleLogo->SetInnerColor(ColorPreset::titleLogo);
	subtitleLogo->SetInnerColor(ColorPreset::titleLogo);

	beInitialized = true;

	layer.AddObject(banner);
	layer.AddObject(titleLogo);
	layer.AddObject(subtitleLogo);
	for (auto& item : systemButtons) {
		layer.AddObject(item);
	}
	for (auto& item : navLinks) {
		layer.AddObject(item);
	}
	for (auto& item : arrowButtons) {
		layer.AddObject(item);
	}
	layer.AddObject(headerLine);

	// フォント追加
	fonts.push_back(FontHandle("mplus60", "M PLUS 2", 60, 100));
	fonts.push_back(FontHandle("smart60", "03スマートフォントUI", 60, 15));
	fonts.push_back(FontHandle("mplus25", "M PLUS 2", 40, 100));
}

void Header::Collide()
{
	layer.Collide();
}

void Header::Update()
{
	RegFonts();

	layer.Update();

	banner->Update();
	for (int i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		if (navLinks[i]->GetMouseSelected()) {
			navLinks[i]->SetMouseOff();
			SceneManager::ChangeScene(sceneSets[i].sceneName, sceneSets[i].scene);
			//SceneManager::ChangeScene(sceneSets[i].sceneName, new DebugScene(), false);
		}
	}
	if (systemButtons[0]->GetMouseSelected()) {
		WindowHwnd::WindowClose(GetMainWindowHandle());
		systemButtons[0]->SetMouseOff();
	}
	if (systemButtons[1]->GetMouseSelected()) {
		if (!WindowHolding::GetWindowMaximized()) {
			WindowHwnd::WindowMaximize(GetMainWindowHandle());
		}
		else
		{
			WindowHwnd::WindowNormalize(GetMainWindowHandle());
		}
		systemButtons[1]->SetMouseOff();
	}
	if (systemButtons[2]->GetMouseSelected()) {
		WindowHwnd::WindowMinimize(GetMainWindowHandle());
		systemButtons[2]->SetMouseOff();
	}
	if (subtitleLogo->GetPos().x != (int)titleLogo->GetTextWidth() + 40.f) {
		subtitleLogo->SetPos(PosVec((int)titleLogo->GetTextWidth() + 40.f, 27.f));
		subtitleLogo->CalcPos();
	}
	if (arrowButtons[0]->GetMouseSelected()) {
		arrowButtons[0]->SetMouseOff();
		SceneManager::ChangeSceneBackward();
	}
	if (arrowButtons[1]->GetMouseSelected()) {
		arrowButtons[1]->SetMouseOff();
		SceneManager::ChangeSceneForward();
	}

	std::string titleName = titleLogo->GetText() + " : " + subtitleLogo->GetText();

	SetMainWindowText(titleName.c_str()); // アプリのタイトル名の変更
}

void Header::Draw()
{
	layer.Draw();
}

void Header::SetSubtitle(std::string subtitle)
{
	if (subtitleLogo->GetText() == subtitle) return;
	subtitleLogo->SetText(subtitle);
}
