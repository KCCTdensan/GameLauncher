#pragma once

#include "ObjectData.h"
#include <string>

#define OBJECT_MAX 256

using namespace std;

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	int ObjectSetup(string stg, int x, int y, int sizeX, int sizeY);
	int ObjectColorSetup(string stg, bool outsideFlag, int outsideColor, int outsideSize, bool insideFlag, int insideColor);
	int ObjectRoundnessSetup(string stg, bool flag, int size);

	void Update();
	void Draw();

private:

	ObjectData object[OBJECT_MAX];
};

