#include "SceneBase.h"

SceneBase::~SceneBase()
{
	for (const auto& font : fonts) {
		FontChest::DeleteFontHandle(font.handleName);
	}
}

void SceneBase::RegFonts()
{
	for (const auto& font : fonts) {
		if (FontChest::GetFontHandle(font.handleName) < 0)
			FontChest::CreateFontHandle(font.handleName, font.fontName, font.size, font.thick, font.type);
	}
}
