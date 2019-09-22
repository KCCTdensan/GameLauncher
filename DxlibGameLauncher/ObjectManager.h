#pragma once

#include "ObjectData.h"
#include "OperationData.h"
#include <string>
#include <array>

constexpr int OBJECT_MAX = 256;

constexpr int ARRANGEMENT_X_LEFT = 0;
constexpr int ARRANGEMENT_X_CENTER = 1;
constexpr int ARRANGEMENT_X_RIGHT = 2;

constexpr int ARRANGEMENT_Y_TOP = 0;
constexpr int ARRANGEMENT_Y_CENTER = 1;
constexpr int ARRANGEMENT_Y_BOTTOM = 2;

constexpr int OBJECT_FONT_GOTHIC = 0;

constexpr int OBJECT_BUTTON = 0;
constexpr int OBJECT_INPUT = 1;


using namespace std;

enum OBJECT_TYPE
{
	BUTTON,
	PICTURE
};

class ObjectManager
{
public:
	ObjectManager();

	int Set					(wstring stg, int x, int y, int sizeX, int sizeY, OBJECT_TYPE type);
	int ColorSet			(wstring stg, bool outsideFlag, int outsideColor, int outsideSize, bool insideFlag, int insideColor); //指定しない場合NULL
	int RoundnessSet		(wstring stg, bool flag, int size = NULL);
	int WritingSet			(wstring stg, bool flag, WCHAR data);
	int WritingFontSet		(wstring stg, int Font = 0, int Color = 0, int arrengementX = 0, int arrengementY = 0);
	int ImageChestSet		(wstring stg, bool flag, const WCHAR* PicPath = NULL, int sizeX = 0, int sizeY = 0, int setX = 0, int setY = 0); //FLAGの時も可 また，setX Y はオブジェクトのスタート地点を0とする

	void Update();
	void Draw();

private:

	std::array<ObjectData, OBJECT_MAX> object;
};

