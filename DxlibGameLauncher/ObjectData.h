#pragma once

#include <string>
#include "DxLib.h"
#include "ObjectEnum.h"


//#define LIST_MAX 64

using namespace std;

#pragma warning(push)
#pragma warning(disable:26495)

struct ObjectData
{
	ObjectData() :
		ExistenceFlag(FALSE),
		EffectiveFlag(TRUE),
		AnimationTick(0),
		WritingFlag(FALSE),
		CanSeeFlag(TRUE),
		FontHandle(0),
		progressFlag(FALSE)
	{

	}

	OBJECT_TYPE ObjectType;

	string name;

	bool ExistenceFlag;//存在フラグ
	bool EffectiveFlag;//有効フラグ
	bool CanSeeFlag;//可視フラグ

	bool ActivationFlag;
	bool MouseFlag;

	int AnimationBlend; // 使用するかは不明
	bool AnimationFlag = TRUE;
	int AnimationTick = 50;

	bool progressFlag;

	float progressRate = 0.0f;
	int progressRange = 0;

	int progressBackColor;
	int progressForwardColor;

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
	string writing;
	int writingX;
	int writingY;
	int WritingWidth;

	int writingColor;
	int writingFont;
	int writingSize;

	int FontHandle;
	bool fontOwnFlag = TRUE;

	int WritingArrengementX;
	int WritingArrengementY;
};

#pragma warning(pop)