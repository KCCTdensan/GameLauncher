#include "PlayerScene.h"

PlayerScene::PlayerScene()
{
}

PlayerScene::PlayerScene(SharingScenes* _sharingScenes)
	: SceneBase(_sharingScenes),
	songTitle(nullptr), songAuthor(nullptr), songHandleName(nullptr)
{
	bg = new RectangleObject(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y));
	bg->SetInnerColor(ColorPreset::bgColor); // ��L�����o�X�ǉ��I�u�W�F�N�g(��ɓ����w�i)
	
	songTitle = new TextObject(
		PosVec(50.f, ApplicationPreference::startScenePos + 50.f), PosVec(),
		"smart40", "�e�X�g������", ColorPreset::textBlack);
	songAuthor = new TextObject(
		PosVec(50.f, ApplicationPreference::startScenePos + 100.f), PosVec(),
		"smart20", "�쐬�Җ�", ColorPreset::textBlack);
	songHandleName = new TextObject(
		PosVec(50.f, ApplicationPreference::startScenePos + 125.f), PosVec(),
		"smart20", "123456", ColorPreset::textBlack);

	startButton = new ButtonObject(
		PosVec(50.f, ApplicationPreference::GetBackgroundSize().y - 150.f),
		PosVec(100.f, 100.f), true, true);
	startButton->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	startButton->SetInnerAnimation(.1f);
	startButton->SetOutlineColor(ColorPreset::yellowButtonOuter, 3.f);

	playBar = new ProgressObject(
		PosVec(50.f, ApplicationPreference::GetBackgroundSize().y - 100.f),
		PosVec(ApplicationPreference::GetBackgroundSize().x - 100.f, 50.f), false);
	playBar->GetSlider()->SetInnerColor(Color255());
	playBar->SetInnerColor(Color255(200, 200, 200));
	playBar->SetOutlineColor(Color255(0, 0, 0), 1.f);

	layer.AddObject(bg);

	layer.AddObject(songTitle);
	layer.AddObject(songAuthor);
	layer.AddObject(songHandleName);
	layer.AddObject(startButton);
	layer.AddObject(playBar);

	// �t�H���g�ǉ�
	fonts.push_back(FontHandle("smart40", "03�X�}�[�g�t�H���gUI", 40, 15));
	fonts.push_back(FontHandle("smart20", "03�X�}�[�g�t�H���gUI", 20, 15));
}

PlayerScene::~PlayerScene()
{
}

void PlayerScene::Collide()
{
	canvases.Collide();
	layer.Collide();
}

void PlayerScene::Update()
{
	RegFonts();

	layer.Update();
	canvases.Update();
}

void PlayerScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
