#pragma once

#include "ObjectData.h"
#include "FontData.h"
#include "OperationData.h"
#include <string>
#include <array>
#include "DxLib.h"

constexpr int OBJECT_MAX = 256;
constexpr int FONT_HANDLE_MAX = 256;

constexpr int ARRANGEMENT_X_LEFT = 1;
constexpr int ARRANGEMENT_X_CENTER = 0;
constexpr int ARRANGEMENT_X_RIGHT = 2;

constexpr int ARRANGEMENT_Y_TOP = 1;
constexpr int ARRANGEMENT_Y_CENTER = 0;
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

	int Set							(wstring stg, int x, int y, int sizeX, int sizeY, OBJECT_TYPE type);
	int ColorSet					(wstring stg, bool outsideFlag, int outsideColor, int outsideSize, bool insideFlag, int insideColor); //指定しない場合NULL
	int RoundnessSet				(wstring stg, bool flag, int size = NULL);
	int WritingSet					(wstring stg, bool flag, wstring data);
	int WritingFontSet				(wstring stg, int Font = 0, int size = 1, int Color = 0, int arrengementX = 0, int arrengementY = 0);
	int WritingFontSetToHandle		(wstring stg, wstring handleName, int Color = 0, int arrengementX = 0, int arrengementY = 0);
	int ImageChestSet				(wstring stg, bool flag, wstring PicPath = NULL, int setX = 0, int setY = 0); //FLAGの時も可 また，setX Y はオブジェクトのスタート地点を0とする
	//delete
	//delete all

	int HandleFontSet		(wstring stg, int font = 0, int size = 15);
	//delete

	void Update();
	void Draw();

private:

	std::array<ObjectData, OBJECT_MAX> object;
	std::array<FontData, FONT_HANDLE_MAX> fontData;
	//ObjectData object[OBJECT_MAX];
};

