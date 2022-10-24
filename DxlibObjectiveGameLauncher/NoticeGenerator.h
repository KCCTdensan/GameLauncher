#pragma once
#include "SharingScenes.h"
#include <string>

class NoticeGenerator
{
public:

	NoticeGenerator(SharingScenes* _sharingScenes)
		: sharingScenes(_sharingScenes) {}

	void MakeNotice(std::string text);

private:

	SharingScenes* sharingScenes;
};

