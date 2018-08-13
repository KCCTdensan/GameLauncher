#include "Gallery.hpp"


void Gallery::DrawBkgnd()
{
	BitBlt(hMemDC, 0, 0, MenuWidth, Height, MenuDC.hMemDC, 0, 0, SRCCOPY);
	BitBlt(hMemDC, MenuWidth, 0, Width - MenuWidth, Height, PreviewDC.hMemDC, 0, 0, SRCCOPY);
}

Gallery::Gallery(SceneManagerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:Scene(SceneChanger, BmpWidth, BmpHeight), MenuWidth(BmpWidth / 4), MenuDC(MenuWidth, BmpHeight), PreviewDC(BmpWidth - MenuWidth, BmpHeight)
{
	ColorBkgnd.Rectangle(MenuDC.hMemDC, 0, 0, MenuWidth, Height);
	ColorBkgnd.Rectangle(PreviewDC.hMemDC, 0, 0, Width - MenuWidth, Height);
}

Gallery::~Gallery()
{

}