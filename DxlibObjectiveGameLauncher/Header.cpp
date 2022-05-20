#include "Header.h"

std::vector<SceneSet> Header::sceneSets = {
	SceneSet("debug", new DebugScene()),
	SceneSet("home", new HomeScene()),
	SceneSet("debug", new DebugScene())
};

std::vector<ButtonObject> Header::navLinks = {};

bool Header::beInitialized = false;

float Header::navWidth = ApplicationPreference::GetBackgroundSize().x - 300;
float Header::height = ApplicationPreference::GetBackgroundSize().y / 10;

void Header::Initialize()
{
	if (beInitialized) return;

	for (int i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		navLinks.push_back(ButtonObject(PosVec((ApplicationPreference::GetBackgroundSize().x - navWidth) / 2.f + navWidth / ApplicationPreference::headerButtonNum * i, 0.f),
			PosVec(navWidth / ApplicationPreference::headerButtonNum, height)));
		navLinks[i].SetInnerColor(GetColor(255, 255, 225), GetColor(230, 230, 200), GetColor(150, 150, 120), GetColor(200, 200, 170));
	}

	beInitialized = true;
}

void Header::Collide()
{
	for (int i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		navLinks[i].Collide();
	}
}

void Header::Update()
{
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
	for (int i = 0; i < ApplicationPreference::headerButtonNum; i++) {
		navLinks[i].Draw();
	}
}
