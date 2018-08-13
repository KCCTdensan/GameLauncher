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
	SelectObject(hMemDC, GetStockObject(NULL_BRUSH));//hMemDC���܂��j������Ă��Ȃ��̂ŁA�ʂ̃u���V��I�����Ă���
	SelectObject(hMemDC, GetStockObject(NULL_PEN));//hMemDC���܂��j������Ă��Ȃ��̂ŁA�ʂ̃y����I�����Ă���
	DeleteObject(hBrushBkgnd);
	DeleteObject(hPenBkgnd);
	DeleteObject(hBrushAccent);
	DeleteObject(hPenAccent);
}