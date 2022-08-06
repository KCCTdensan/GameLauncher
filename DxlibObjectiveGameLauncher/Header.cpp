#include "Header.h"

std::vector<SceneSet> Header::sceneSets = {
	SceneSet("debug", new DebugScene()),
	SceneSet("home", new HomeScene()),
	SceneSet("debug", new DebugScene())
};

std::vector<ButtonObject> Header::navLinks = {};
std::vector<ButtonObject> Header::systemButtons = {};

bool Header::beInitialized = false;

float Header::navWidth = ApplicationPreference::GetBackgroundSize().x - 300;
float Header::height = ApplicationPreference::GetBackgroundSize().y / 12.f;

RectangleObject Header::banner = RectangleObject(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y / 15.f));
LineObject Header::headerLine = LineObject(
	PosVec(0.f, ApplicationPreference::GetBackgroundSize().y / 15.f),
	PosVec(
		ApplicationPreference::GetBackgroundSize().x,
		ApplicationPreference::GetBackgroundSize().y / 15.f)
);

void Header::Initialize()
{
	if (beInitialized) return;

	banner.SetInnerColor(GetColor(20, 20, 20));

	for (int i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		navLinks.push_back(ButtonObject(PosVec(ApplicationPreference::GetBackgroundSize().x - (navWidth / ApplicationPreference::headerButtonNum * (ApplicationPreference::headerButtonNum - i)), ApplicationPreference::GetBackgroundSize().y / 15.f),
			PosVec(navWidth / ApplicationPreference::headerButtonNum, height)));
		navLinks[i].SetInnerColor(Color255(255, 255, 225), Color255(230, 230, 200), Color255(150, 150, 120), Color255(200, 200, 170));
		navLinks[i].SetInnerAnimation(0.2f);
	}

	for (int i = 0; i < 3; i++) {
		systemButtons.push_back(ButtonObject(
			PosVec(
				ApplicationPreference::GetBackgroundSize().x - 60.f - 60.f * i,
				0.f),
			PosVec(60.f, 40.f), true, true));
		if (i == 0)
			systemButtons[i].SetInnerColor(Color255(30, 30, 30), Color255(220, 113, 114), Color255(184, 85, 85), Color255(184, 85, 85));
		else
			systemButtons[i].SetInnerColor(Color255(30, 30, 30), Color255(50, 50, 50), Color255(10, 10, 10), Color255(30, 30, 30));
		systemButtons[i].SetOutlineColor(Color255(255, 255, 255), 1.f);
		systemButtons[i].SetInnerAnimation(0.2f);
	}
	headerLine.SetEnabledOutline(true);
	headerLine.SetOutlineColor(Color255(0xFF, 0x77, 0xFE), 2.5f);

	beInitialized = true;
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
	banner.Update();
	for (int i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		navLinks[i].Update();

		if (navLinks[i].GetMouseSelected()) {
			navLinks[i].SetMouseOff();
			SceneManager::ChangeScene(sceneSets[i].sceneName, sceneSets[i].scene);
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
	headerLine.Draw();
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
	DrawBoxAA(0, 0, 1920, 1080, GetColor(255, 255, 255), false, 2.); // debug
}
