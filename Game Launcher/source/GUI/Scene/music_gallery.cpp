#include "music_gallery.hpp"


MusicGallery::MusicGallery(HWND hWnd, SceneChangerInterface *sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight)
	:Gallery(hWnd, sceneChanger, bmpWidth, bmpHeight)
{

}

int MusicGallery::initialize()
{
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int MusicGallery::finalize()
{
	return 0;
}

int MusicGallery::buttonLUp(unsigned short x, unsigned short y, unsigned int param)
{
	return 0;
}

int MusicGallery::update()
{
	return 0;
}
