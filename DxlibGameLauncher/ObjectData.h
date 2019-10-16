#pragma once

#include "DxLib.h"
#include "OperationData.h"
#include <string>


#define LIST_MAX 64

using namespace std;

#pragma warning(push)
#pragma warning(disable:26495)

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
	int AnimationTick = 50;

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
	wstring writing;
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

#pragma warning(pop)

