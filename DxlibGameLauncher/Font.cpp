#include "Font.h"
#include "GetExePath.h"
#include "AppData.h"
#include "OperationData.h"


Font::Font()
{
	ReadFont();
}


Font::~Font()
{
	SetCurrentDirectory(Path::GetAppPath());
	switch (App::RELEASE_FLAG)
	{
	case TRUE:
		RemoveFontResource(".\\Fonts\\PixelMplus12-Regular.ttf");//Pixel レギュラー・ボールド
		RemoveFontResource(".\\Fonts\\PixelMplus12-Bold.ttf");
		break;

	case FALSE:
		RemoveFontResource("..\\Fonts\\PixelMplus12-Regular.ttf");//Pixel レギュラー・ボールド
		RemoveFontResource("..\\Fonts\\PixelMplus12-Bold.ttf");
		break;
	}
}

/*int Font::FontCreateOtherSize(FONT_TYPE Font_Type, int CreateSize)
{
	int i = -1;
	switch (Font_Type)
	{
	case PIXEL_R:
		i = CreateFontToHandle("PixelMplus12 Regular", CreateSize, -1);
		break;
	case PIXEL_B:
		i = CreateFontToHandle("PixelMplus12 Bold", CreateSize, -1);
		break;
	case GOTHIC:
		i = CreateFontToHandle("MS PGothic", CreateSize, -1);
		break;

	}
	return i;
}*/

void Font::ReadFont()
{
	SetCurrentDirectory(Path::GetAppPath());
	switch (App::RELEASE_FLAG)
	{
	case TRUE:
		AddFontResourceEx(".\\Fonts\\PixelMplus12-Regular.ttf", FR_PRIVATE, NULL);//Pixel レギュラー・ボールド
		AddFontResourceEx(".\\Fonts\\PixelMplus12-Bold.ttf", FR_PRIVATE, NULL);
		break;

	case FALSE:
		if (AddFontResourceEx("..\\Fonts\\PixelMplus12-Regular.ttf", FR_PRIVATE, NULL) <= 0)
		{
			Ope::APPLICATION_END_FLAG = TRUE;
		};//Pixel レギュラー・ボールド
		AddFontResourceEx("..\\Fonts\\PixelMplus12-Bold.ttf", FR_PRIVATE, NULL);
		break;

	}


	/*if (FONT_DEFAULT_PIXEL_REGULAR_HANDLE == -1 || FONT_DEFAULT_PIXEL_BOLD_HANDLE == -1 || FONT_DEFAULT_GOTHIC_HANDLE == -1) {
		Ope::APPLICATION_END_FLAG = TRUE;

		SetCurrentDirectory(Path::GetPath());
		switch (App::RELEASE_FLAG)
		{
		case TRUE:
			RemoveFontResource(".\\Fonts\\PixelMplus12-Regular.ttf");//Pixel レギュラー・ボールド
			RemoveFontResource(".\\Fonts\\PixelMplus12-Bold.ttf");
			break;

		case FALSE:
			RemoveFontResource("..\\Fonts\\PixelMplus12-Regular.ttf");//Pixel レギュラー・ボールド
			RemoveFontResource("..\\Fonts\\PixelMplus12-Bold.ttf");
			break;

		}
	}*/

	return;
}
