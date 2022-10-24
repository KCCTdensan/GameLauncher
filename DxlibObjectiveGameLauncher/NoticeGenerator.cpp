#include "NoticeGenerator.h"
#include "PopupScene.h"

void NoticeGenerator::MakeNotice(std::string text)
{
	sharingScenes->popupScene->MakeNotice(text);
}
