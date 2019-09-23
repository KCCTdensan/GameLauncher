#pragma once

#include "DxLib.h"
#include "OperationData.h"
#include <string>


#define LIST_MAX 64

using namespace std;

struct ObjectData
{
	ObjectData()
		: AnimationTick(0), WritingFlag(FALSE)
	{

	}

	bool ActivationFlag;
	bool MouseFlag;

	int AnimationBlend;
	bool AnimationFlag;
	int AnimationTick = 0;

	bool RoundnessFlag;
	int RoundnessSize;

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