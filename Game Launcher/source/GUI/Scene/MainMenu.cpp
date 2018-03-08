#include "MainMenu.hpp"


MainMenu::MainMenu(HWND hWnd, SceneChangerInterface*SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight) :Scene(SceneChanger, BmpWidth, BmpHeight)
{
	hBrushBkgnd = CreateSolidBrush(BkgndColor);
	hPenBkgnd = CreatePen(PS_SOLID, 0, BkgndColor);
}

MainMenu::~MainMenu()
{
	HDC hdc = GethMemDC();
	SelectObject(hdc, GetStockObject(NULL_BRUSH));//hMemDCがまだ破棄されていないので、別のブラシを選択しておく
	SelectObject(hdc, GetStockObject(NULL_PEN));//hMemDCがまだ破棄されていないので、別のペンを選択しておく
	DeleteObject(hBrushBkgnd);
	DeleteObject(hPenBkgnd);
	hBrushBkgnd = NULL;
	hPenBkgnd = NULL;
}

int MainMenu::Initialize(HWND hWnd)
{
	HDC hdc = GethMemDC();

	//背景を塗りつぶす
	SelectObject(hdc, hBrushBkgnd);
	SelectObject(hdc, hPenBkgnd);
	Rectangle(hdc, 0, 0, GetWidth(), GetHeight());
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
	DestroyWindow(hWnd);
	return 0;
}

int MainMenu::Update(HWND hWnd)
{
	return 0;
}