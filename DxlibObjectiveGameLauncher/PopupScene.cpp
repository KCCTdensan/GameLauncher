#include "PopupScene.h"

PopupScene::PopupScene()
{
	musicCanvas = new MusicCanvas();
	popupMusic.Setup(musicCanvas);

	noticeCanvas = new NoticeCanvas();
	popupNotice.Setup(noticeCanvas);

	//popups.push_back(popupWindow);
	popups.push_back(popupNotice);

	// ƒtƒHƒ“ƒg’Ç‰Á
	fonts.push_back(FontHandle("mplus20", "M PLUS 2", 20, 100));
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
	RegFonts();

	for (auto& item : popups) {
		item.ItemUpdate();
	}

	for (auto& item : popups) {
		item.CanvasUpdate();
	}

	for (auto& item : popups) {
		item.UpdateAction();
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

void PopupScene::MakeNotice(std::string text)
{
	noticeCanvas->MakeNotice(text);
}
