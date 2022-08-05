#include "ApplicationBuilder.h"

ApplicationBuilder::ApplicationBuilder()
{
	tmp = ApplicationPreference::clientAssets + "\\fonts\\03�X�}�[�g�t�H���gUI.otf";
	// Font��ǉ�
	if (AddFontResourceEx(tmp.c_str(), FR_PRIVATE, NULL) <= 0) {
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}
	tmp = ApplicationPreference::clientAssets + "\\fonts\\MPLUS2-Medium.ttf";
	// Font��ǉ�
	if (AddFontResourceEx(tmp.c_str(), FR_PRIVATE, NULL) <= 0) {
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

	ApplicationTime::Initialize();
}

ApplicationBuilder::~ApplicationBuilder()
{
	RemoveFontResourceEx(tmp.c_str(), FR_PRIVATE, NULL);
}

void ApplicationBuilder::Update()
{
	ApplicationTime::Update();
	WindowHolding::Update();
}
