#pragma once

#include "DxLib.h"
#include "OperationData.h"
#include <string>


#define LIST_MAX 64

using namespace std;


struct ObjectData
{
	ObjectData()
		: ExistenceFlag(FALSE), EffectiveFlag(TRUE), AnimationTick(0), WritingFlag(FALSE)
	{

	}

	int ObjectType;

	wstring name;

	bool ExistenceFlag;//存在フラグ
	bool EffectiveFlag;//有効フラグ

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

	bool WritingFlag;
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

