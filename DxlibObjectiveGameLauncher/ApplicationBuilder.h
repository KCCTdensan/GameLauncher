#pragma once
#include "FontChest.h"
#include "ApplicationPreference.h"
#include "ApplicationTime.h"
#include "WindowHolding.h"
#include "Color255.h"
#include <locale.h>


class ApplicationBuilder
{
public:
	ApplicationBuilder(); // 起動時に呼び出される
	~ApplicationBuilder();

	void Update();

private:
	std::string tmp;
};

