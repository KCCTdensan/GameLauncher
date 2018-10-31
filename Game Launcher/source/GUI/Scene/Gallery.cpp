#include "Gallery.hpp"


item_button::item_button(unsigned short Width, unsigned short Height)
	:mem_dc(Width, Height)
{

}

item_button::~item_button()
{

}

const color gallery::ColorAccent[MAX_CATEGORY] = {
	RGB(0xdf, 0x3f, 0x3f),
	RGB(0xbf, 0xbf, 0x3f),
	RGB(0xaf, 0x2f, 0x9f),
	RGB(0x2f, 0xaf, 0xaf),
	RGB(0x2f, 0x5f, 0xdf),
	RGB(0x2f, 0xdf, 0x5f),
	RGB(0x7f, 0x7f, 0x7f)
};

void gallery::DrawBkgnd()
{
	BitBlt(hMemDC, 0, 0, MenuWidth, Height, MenuDC.hMemDC, 0, 0, SRCCOPY);
	BitBlt(hMemDC, MenuWidth, 0, Width - MenuWidth, Height, PreviewDC.hMemDC, 0, 0, SRCCOPY);
}

gallery::gallery(scene_manager_interface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:scene(SceneChanger, BmpWidth, BmpHeight), MenuWidth(BmpWidth / 4), MenuDC(MenuWidth, BmpHeight), PreviewDC(BmpWidth - MenuWidth, BmpHeight)
{
	ColorBkgnd.Rectangle(MenuDC.hMemDC, 0, 0, MenuWidth, Height);
	ColorBkgnd.Rectangle(PreviewDC.hMemDC, 0, 0, Width - MenuWidth, Height);
}

gallery::~gallery()
{

}