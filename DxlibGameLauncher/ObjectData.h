#pragma once

#include "DxLib.h"
#include "OperationData.h"

#define LIST_MAX 64

using namespace std;


class ObjectData
{
public:
	ObjectData();
	~ObjectData();

	int ObjectType;

	WCHAR name;

	bool ExistenceFlag = FALSE;//存在フラグ
	bool EffectiveFlag = TRUE;//有効フラグ

	bool ActivationFlag;
	bool MouseFlag;

	int AnimationBlend;
	bool AnimationFlag;
	int AnimationTick = 0;

	bool RoundnessFlag;
	int RoundnessSize;

	int x;
	int y;
	int xSize;
	int ySize;

	bool insideFlag;
	bool outsideFlag;
	int insideColor;
	int outsideColor;
	int outsidePixel;
	
	bool pictureFlag;
	int pictureNum;
	int pictureNumTmp;

	int pictureX;
	int pictureY;

	bool WritingFlag = FALSE;
	WCHAR writing;
	int writingX;
	int writingY;
	int WritingWidth;

	int writingColor;
	int writingFont;
	int writingSize;

	int FontHandle;

	int WritingArrengementX;
	int WritingArrengementY;
};

