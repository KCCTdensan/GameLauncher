#include "MainMenu.hpp"


MainMenu::MainMenu(HWND hWnd, SceneChangerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:Scene(SceneChanger, BmpWidth, BmpHeight)
{
	int Split = ((MAX_CATEGORY / 2) + 1) * 2;
	int Block = BmpWidth / Split;
	int GalleryButtonWidth = Block * 5 / 6;
	for(int i = 0; i < MAX_CATEGORY; ++i)
	{
		GalleryButtons[i].left = (Split == MAX_CATEGORY) ? Block * i + Block / 10 : Block * i + Block / 2 + Block / 10;
		GalleryButtons[i].top = (BmpHeight - GalleryButtonWidth) / 2;
		GalleryButtons[i].right = GalleryButtons[i].left + GalleryButtonWidth;
		GalleryButtons[i].bottom = GalleryButtons[i].top + GalleryButtonWidth;
	}
}

MainMenu::~MainMenu()
{

}

int MainMenu::Initialize(HWND hWnd)
{
	ColorBkgnd.Rectangle(hMemDC, 0, 0, Width, Height);
	for(int i = 0; i < MAX_CATEGORY; ++i)
	{
		ColorAccent[i].Rectangle(hMemDC, GalleryButtons[i]);
	}
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);

	return 0;
}

int MainMenu::Finalize(HWND hWnd)
{
	return 0;
}

int MainMenu::LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int MainMenu::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	POINT MousePoint;
	MousePoint.x = LOWORD(lp);
	MousePoint.y = HIWORD(lp);
	for(int i = 0; i < MAX_CATEGORY; ++i)
	{
		if(PtInRect(&GalleryButtons[i], MousePoint))
		{
			SceneChanger->ChangeScene(hWnd, (SceneName)(i + 1));
		}
	}
	return 0;
}

int MainMenu::Update(HWND hWnd)
{
	return 0;
}