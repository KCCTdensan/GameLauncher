#include "AppGallery.hpp"


app_gallery::app_gallery(HWND hWnd, scene_manager_interface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:gallery(SceneChanger, BmpWidth, BmpHeight)
{
	Items = ItemManager::GetItems(CAT_APP);
	Buttons.resize(Items.size());
	for (int i = 0; i < Items.size(); ++i)
	{
		Buttons[i] = new item_button(BmpWidth, BmpHeight / 10);
	}
}

app_gallery::~app_gallery()
{
	int NumButtons = (int)Buttons.size();
	for (int i = 0; i < NumButtons; ++i)
	{
		delete Buttons[i];
	}
}

int app_gallery::Initialize(HWND hWnd)
{
	DrawBkgnd();
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int app_gallery::Finalize(HWND hWnd)
{
	return 0;
}

int app_gallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int app_gallery::Update(HWND hWnd)
{
	return 0;
}
