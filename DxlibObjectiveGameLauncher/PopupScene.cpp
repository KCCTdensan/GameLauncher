#include "PopupScene.h"

PopupScene::PopupScene()
{
}

PopupScene::PopupScene(SharingScenes* _sharingScenes)
	: SceneBase(_sharingScenes)
{
}

void PopupScene::Collide()
{
	for (auto& item : popups) {
		item.ItemCollide();
	}
}

void PopupScene::Update()
{
	for (auto& item : popups) {
		item.ItemUpdate();
	}
}

void PopupScene::Draw()
{
	for (auto& item : popups) {
		item.ItemDraw();
	}
}
