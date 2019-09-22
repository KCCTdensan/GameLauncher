#pragma once

#include "ObjectData.h"
#include <string>
#include "OperationData.h"

#define OBJECT_MAX 256

#define ARRANGEMENT_X_LEFT		0
#define ARRANGEMENT_X_CENTER	1
#define ARRANGEMENT_X_RIGHT		2

#define ARRANGEMENT_Y_TOP		0
#define ARRANGEMENT_Y_CENTER	1
#define ARRANGEMENT_Y_BOTTOM	2

#define OBJECT_FONT_GOTHIC		0

#define OBJECT_BUTTON			0
#define OBJECT_INPUT			1

using namespace std;

enum OBJECT_TYPE {
	BUTTON,
	PICTURE
};

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	int Set					(WCHAR stg, int x, int y, int sizeX, int sizeY, OBJECT_TYPE type);
	int ColorSet			(WCHAR stg, bool outsideFlag, int outsideColor, int outsideSize, bool insideFlag, int insideColor); //指定しない場合NULL
	int RoundnessSet		(WCHAR stg, bool flag, int size = NULL);
	int WritingSet			(WCHAR stg, bool flag, WCHAR data);
	int WritingFontSet		(WCHAR stg, int Font = 0, int Color = 0, int arrengementX = 0, int arrengementY = 0);
	int ImageChestSet		(WCHAR stg, bool flag, TCHAR PicPath = NULL, int sizeX = 0, int sizeY = 0, int setX = 0, int setY = 0); //FLAGの時も可 また，setX Y はオブジェクトのスタート地点を0とする

	void Update();
	void Draw();

private:

	ObjectData object[OBJECT_MAX];
};

