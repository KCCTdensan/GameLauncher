#pragma once
#include <vector>
#include <string>
#include "FontChest.h"
#include "ObjectLayer.h"
#include "FontHandleData.h"

class SceneBase
{
public:
	SceneBase()
		: fonts(), layer() {};
	~SceneBase();

	virtual void Collide() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	void RegFonts();

	std::vector<FontHandle> fonts;

	ObjectLayer layer;
};

