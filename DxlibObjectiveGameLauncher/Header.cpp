#include "Header.h"

std::vector<SceneSet> Header::sceneSets = {
	SceneSet("debug", new DebugScene()),
	SceneSet("home", new HomeScene()),
	SceneSet("debug", new DebugScene())
};

std::vector<ButtonObject> Header::navLinks = {};

bool Header::beInitialized = false;

float Header::navWidth = ApplicationPreference::GetBackgroundSize().x - 300;
float Header::height = ApplicationPreference::GetBackgroundSize().y / 12.f;

RectangleObject Header::banner = RectangleObject(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y / 12.f));

void Header::Initialize()
{
	if (beInitialized) return;

	banner.SetInnerColor(GetColor(35, 35, 35));

	for (int i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		navLinks.push_back(ButtonObject(PosVec(ApplicationPreference::GetBackgroundSize().x - (navWidth / ApplicationPreference::headerButtonNum * (ApplicationPreference::headerButtonNum - i)), ApplicationPreference::GetBackgroundSize().y / 12.f),
			PosVec(navWidth / ApplicationPreference::headerButtonNum, height)));
		navLinks[i].SetInnerColor(GetColor(255, 255, 225), GetColor(230, 230, 200), GetColor(150, 150, 120), GetColor(200, 200, 170));
	}

	beInitialized = true;
}

void Header::Collide()
{
	banner.Collide();
	for (int i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		navLinks[i].Collide();
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
}

void Header::Draw()
{
	banner.Draw();
	for (int i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		navLinks[i].Draw();
	}
}
