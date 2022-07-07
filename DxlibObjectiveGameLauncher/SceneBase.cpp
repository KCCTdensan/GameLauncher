#include "SceneBase.h"

SceneBase::~SceneBase()
{
	for (const auto& font : fonts) {
		FontData::DeleteFontHandle(font.handleName);
	}
}

void SceneBase::RegFonts()
{
	for (const auto& font : fonts) {
		if (FontData::GetFontHandle(font.handleName) < 0)
			FontData::CreateFontHandle(font.handleName, font.fontName, font.size, font.thick, font.type);
	}
}
