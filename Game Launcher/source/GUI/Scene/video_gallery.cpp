#include "video_gallery.hpp"


VideoGallery::VideoGallery(HWND hWnd, SceneChangerInterface *sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight)
	:Gallery(hWnd, sceneChanger, bmpWidth, bmpHeight)
{

}

int VideoGallery::initialize()
{
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int VideoGallery::finalize()
{
	return 0;
}

int VideoGallery::buttonLUp(unsigned short x, unsigned short y, unsigned int param)
{
	return 0;
}

int VideoGallery::update()
{
	return 0;
}
