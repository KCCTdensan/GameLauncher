#include "gallery.hpp"


Gallery::Gallery(HWND hWnd, SceneChangerInterface* sceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	: Scene(hWnd, sceneChanger, BmpWidth, BmpHeight)
{
	hBrushBkgnd = CreateSolidBrush(BkgndColor);
	hPenBkgnd = CreatePen(PS_SOLID, 0, BkgndColor);
}

Gallery::~Gallery()
{
	SelectObject(hMemDC, GetStockObject(NULL_BRUSH));//hMemDCがまだ破棄されていないので、別のブラシを選択しておく
	SelectObject(hMemDC, GetStockObject(NULL_PEN));//hMemDCがまだ破棄されていないので、別のペンを選択しておく
	DeleteObject(hBrushBkgnd);
	DeleteObject(hPenBkgnd);
	hBrushBkgnd = NULL;
	hPenBkgnd = NULL;
}