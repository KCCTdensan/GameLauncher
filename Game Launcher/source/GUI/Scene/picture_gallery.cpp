#include "picture_gallery.hpp"


PictureGallery::PictureGallery(HWND hWnd, SceneChangerInterface *sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight)
	:Gallery(hWnd, sceneChanger, bmpWidth, bmpHeight)
{

}

int PictureGallery::initialize()
{
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int PictureGallery::finalize()
{
	return 0;
}

int PictureGallery::buttonLUp(unsigned short x, unsigned short y, unsigned int param)
{
	return 0;
}

int PictureGallery::update()
{
	return 0;
}
