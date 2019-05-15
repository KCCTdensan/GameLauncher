#include "game_gallery.hpp"


GameGallery::GameGallery(HWND hWnd, SceneChangerInterface *sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight)
	:Gallery(hWnd, sceneChanger, bmpWidth, bmpHeight)
{

}

int GameGallery::initialize()
{
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int GameGallery::finalize()
{
	return 0;
}

int GameGallery::buttonLUp(unsigned short x, unsigned short y, unsigned int param)
{
	return 0;
}

int GameGallery::update()
{
	return 0;
}