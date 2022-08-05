#pragma once
#include "PositionVector.h"
#include "UUIDGenerator.h"
#include "ObjectOverlapping.h"
#include "ApplicationTime.h"
#include "Color255.h"
#include <vector>

class ObjectBase
{
protected:
	ObjectBase(PosVec _pos, PosVec _size)
		:pos(_pos), size(_size), enabled(true), mouseHit(false), mouseClicked(false), mouseSelected(false),
		children{}, beCalledNoMouse(false), guid(),
		currentInnerColor(0), animationStartColor(0), animationEndColor(0), animationDuraion(0.f), animationCurrentlyRate(0.f),
		animationEnabled(false), mRed(0.f), mGreen(0.f), mBlue(0.f), animationElapsedTime(0.f), animationDuraionRemain(0.f)
	{
		UUIDGenerator uuidGenerator;
		guid = uuidGenerator.GetGUID();
	}

	virtual void Update() = 0;
	virtual void Draw() = 0;

	void CheckGUID() { if (ObjectOverlapping::GetGUID() != guid) SetNoMouseWithClick(); }

	void SetAnimationPoint(Color255 _start, Color255 _goal);

	PosVec pos;
	PosVec size;

	bool enabled;

	bool mouseHit;
	bool mouseSelected;
	bool mouseClicked;
	bool beCalledNoMouse;

	std::string guid;

	Color255 currentInnerColor;

	bool animationEnabled;

	Color255 animationStartColor;
	Color255 animationEndColor;
	float mRed;
	float mGreen;
	float mBlue;

	float animationDuraion;
	float animationDuraionRemain;
	float animationElapsedTime;
	float animationCurrentlyRate;

private:
	std::vector<ObjectBase*> children;

public:
	bool SetEnabled(bool _enabled) { enabled = _enabled; return true; }
	bool SetEnabled() { return enabled; }

	// ��Ƀ��C�����d�Ȃ��Ă����ꍇ�̉�������
	bool SetNoMouse() { mouseHit = false; return true; }
	bool SetNoMouseWithClick() { mouseHit = false; mouseClicked = false; /*beCalledNoMouse = true;*/ return true; }

	// �}�E�X���͉���(Selected�Ȃǂ̔C�ӂ̕����ɌĂяo����)
	bool SetMouseOff() { mouseClicked = false; mouseSelected = false; return true; }

	// �}�E�X����n�擾
	bool GetMouseHit() { return mouseHit; }
	bool GetMouseClicked() { return mouseClicked; }
	bool GetMouseSelected() { return mouseSelected; }

	// �A�j���[�V�����ݒ�
	bool SetAnimation(float _duration) { animationEnabled = true; animationDuraion = _duration; animationDuraionRemain = _duration; animationElapsedTime = 0.f; return true; }
	bool SetAnimation() { animationEnabled = false; return true; }

	// �e(����)�݈̂ړ�(��Βl)
	bool SetPos(PosVec _pos) { pos = _pos; return true; }

	// �I�u�W�F�N�g�ړ��n(�q�v�f�܂�)
	bool Move(PosVec _delta);

	// �q�v�f�o�^
	bool RegisterChildren(ObjectBase* _object) { children.push_back(_object); return true; }

	// �����ɎQ�Ɠn�����ꂽ��ʏ��Ȃǂ̍\���̂���ꂽ�������������H
};

