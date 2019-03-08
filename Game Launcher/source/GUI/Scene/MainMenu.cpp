#include "MainMenu.hpp"


MainMenu::MainMenu(HWND hWnd, SceneChangerInterface* SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight) :Scene(SceneChanger, BmpWidth, BmpHeight)
{
	hBrushBkgnd = CreateSolidBrush(BkgndColor);
	hPenBkgnd = CreatePen(PS_SOLID, 0, BkgndColor);
}

MainMenu::~MainMenu()
{
	SelectObject(hMemDC, GetStockObject(NULL_BRUSH));//hMemDCがまだ破棄されていないので、別のブラシを選択しておく
	SelectObject(hMemDC, GetStockObject(NULL_PEN));//hMemDCがまだ破棄されていないので、別のペンを選択しておく
	DeleteObject(hBrushBkgnd);
	DeleteObject(hPenBkgnd);
	hBrushBkgnd = NULL;
	hPenBkgnd = NULL;
}

int MainMenu::Initialize(HWND hWnd)
{
	//背景を塗りつぶす
	SelectObject(hMemDC, hBrushBkgnd);
	SelectObject(hMemDC, hPenBkgnd);
	Rectangle(hMemDC, 0, 0, Width, Height);
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);

	return 0;
}

int MainMenu::Finalize(HWND hWnd)
{
	return 0;
}

int MainMenu::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int MainMenu::Update(HWND hWnd)
{
	return 0;
}