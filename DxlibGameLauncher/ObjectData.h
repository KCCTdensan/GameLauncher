#pragma once
#include "DxLib.h"
class ObjectData
{
public:
	ObjectData();
	~ObjectData();

	bool ExistenceFlag = FALSE;//���݃t���O
	bool EffectiveFlag = TRUE;//�L���t���O

	bool ActivationFlag;
	bool AnimationFlag;

	bool RoundnessFlag;
	int RoundnessSize;

	int x;
	int y;
	int xSize;
	int ySize;

};

