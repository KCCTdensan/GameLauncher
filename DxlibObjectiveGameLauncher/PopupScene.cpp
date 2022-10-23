#include "PopupScene.h"

PopupScene::PopupScene()
{
	musicCanvas = new MusicCanvas();
	popupMusic.Setup(musicCanvas);

	noticeCanvas = new NoticeCanvas();
	popupNotice.Setup(noticeCanvas);

	//popups.push_back(popupWindow);
	popups.push_back(popupNotice);
}

void PopupScene::Collide()
{
	for (auto& item : popups) {
		item.ItemCollide();
	}

	for (auto& item : popups) {
		item.CanvasCollide();
	}
}

void PopupScene::Update()
{
	for (auto& item : popups) {
		item.ItemUpdate();
	}

	for (auto& item : popups) {
		item.CanvasUpdate();
	}
}

void PopupScene::Draw()
{
	for (auto& item : popups) {
		item.ItemDraw();
	}

	for (auto& item : popups) {
		item.CanvasDraw();
	}
}
