#include "GameGallery.hpp"


GameGallery::GameGallery(HWND hWnd, SceneChangerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:Gallery(SceneChanger, BmpWidth, BmpHeight)
{

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
	Gallery::LButtonUp(hWnd, wp, lp);
	return 0;
}

int GameGallery::Update(HWND hWnd)
{
	return 0;
}
