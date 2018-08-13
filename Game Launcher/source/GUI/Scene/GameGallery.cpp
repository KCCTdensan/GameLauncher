#include "GameGallery.hpp"


GameGallery::GameGallery(HWND hWnd, SceneChangerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:Gallery(SceneChanger, BmpWidth, BmpHeight, RGB(0xbf, 0xbf, 0x3f))
{

}

GameGallery::~GameGallery()
{

}

int GameGallery::Initialize(HWND hWnd)
{
	return 0;
}

int GameGallery::Finalize(HWND hWnd)
{
	return 0;
}

int GameGallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int GameGallery::Update(HWND hWnd)
{
	return 0;
}
