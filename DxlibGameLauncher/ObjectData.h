#pragma once
#include <string>
#include "DxLib.h"
#define LIST_MAX 64

class ObjectData
{
public:
	ObjectData();
	~ObjectData();

	int ObjectType;

	bool ExistenceFlag = FALSE;//存在フラグ
	bool EffectiveFlag = TRUE;//有効フラグ

	bool ActivationFlag;

	int AnimationBlend;
	bool AnimationFlag;
	int AnimationTick = 0;

	bool RoundnessFlag;
	int RoundnessSize;

	int x;
	int y;
	int xSize;
	int ySize;

	int pictureHandleTmp;
	int pictureHandle;

	bool WritingFlag = FALSE;
	string writing;
	int writingX;
	int writingY;
	int WritingWidth;

	int writingColor;
	int writingFont;
	int writingSize;

	bool ListFlag;
	int ListArrengement;
	string ListData[LIST_MAX];
	int ListDataX[LIST_MAX];
	int ListDataY[LIST_MAX];
	int ListDataWidth[LIST_MAX];
	int ListOneSizeheight[LIST_MAX];
};

