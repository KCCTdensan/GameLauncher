#include "GameGallery.hpp"


GameGallery::GameGallery(HWND hWnd, SceneManagerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:Gallery(SceneChanger, BmpWidth, BmpHeight)
{
	Items = ItemManager::GetItems(CAT_GAME);
}

GameGallery::~GameGallery()
{

}

int GameGallery::Initialize(HWND hWnd)
{
	DrawBkgnd();
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int GameGallery::Finalize(HWND hWnd)
{
	return 0;
}

int GameGallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int GameGallery::Update(HWND hWnd)
{
	return 0;
}
