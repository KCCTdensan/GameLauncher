#pragma once

#include "ObjectData.h"
#include <string>

#define OBJECT_MAX 256

#define ARRANGEMENT_LEFT	0
#define ARRANGEMENT_CENTER	1
#define ARRANGEMENT_RIGHT	2

#define OBJECT_FONT_GOTHIC 0

using namespace std;

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	int Set(string stg, int x, int y, int sizeX, int sizeY);
	int ColorSet(string stg, bool outsideFlag, int outsideColor, int outsideSize, bool insideFlag, int insideColor);
	int RoundnessSet(string stg, bool flag, int size);
	int WritingSet(string stg, bool flag, wstring data);
	int WritingFontSet(string stg, int Font = 0, int Color = 0, int arrengement = 0);

	void Update();
	void Draw();

private:

	ObjectData object[OBJECT_MAX];
};

