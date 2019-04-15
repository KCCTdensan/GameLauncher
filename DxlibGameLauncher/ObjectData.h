#pragma once
#include "DxLib.h"
class ObjectData
{
public:
	ObjectData();
	~ObjectData();

	bool ExistenceFlag = FALSE;//存在フラグ
	bool EffectiveFlag = TRUE;//有効フラグ

	bool ActivationFlag;
	bool AnimationFlag;

	bool RoundnessFlag;
	int RoundnessSize;

	int x;
	int y;
	int xSize;
	int ySize;

};

