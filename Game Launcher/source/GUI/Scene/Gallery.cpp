#include "Gallery.hpp"


Gallery::Gallery(SceneChangerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight, COLORREF AccentColor)
	:Scene(SceneChanger, BmpWidth, BmpHeight), AccentColor(AccentColor)
{
	hBrushBkgnd = CreateSolidBrush(BkgndColor);
	hPenBkgnd = CreatePen(PS_SOLID, 0, BkgndColor);
	hBrushAccent = CreateSolidBrush(AccentColor);
	hPenAccent = CreatePen(PS_SOLID, 0, AccentColor);
}

Gallery::~Gallery()
{
	SelectObject(hMemDC, GetStockObject(NULL_BRUSH));//hMemDCがまだ破棄されていないので、別のブラシを選択しておく
	SelectObject(hMemDC, GetStockObject(NULL_PEN));//hMemDCがまだ破棄されていないので、別のペンを選択しておく
	DeleteObject(hBrushBkgnd);
	DeleteObject(hPenBkgnd);
	DeleteObject(hBrushAccent);
	DeleteObject(hPenAccent);
}