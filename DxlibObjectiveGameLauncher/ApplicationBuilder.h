#pragma once
#include "FontChest.h"
#include "ApplicationPreference.h"
#include "ApplicationTime.h"
#include "WindowHolding.h"

class ApplicationBuilder
{
public:
	ApplicationBuilder(); // �N�����ɌĂяo�����
	~ApplicationBuilder();

	void Update();

private:
	std::string tmp;
};

