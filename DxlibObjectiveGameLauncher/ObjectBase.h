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
		:pos(_pos), size(_size),
		enabled(true), mouseHit(false), mouseClicked(false), mouseSelected(false),
		children{}, beCalledNoMouse(false), guid(),
		currentInnerColor(0),
		animationStartInnerColor(0),
		animationEndInnerColor(0),
		animationInnerDuration(0.f),
		animationInnerCurrentlyRate(0.f),
		animationInnerEnabled(false),
		animationOuterEnabled(false),
		mInnerRed(0.f),
		mInnerGreen(0.f),
		mInnerBlue(0.f),
		mOuterRed(0.f),
		mOuterGreen(0.f),
		mOuterBlue(0.f),
		animationInnerElapsedTime(0.f),
		animationInnerDuraionRemain(0.f),
		currentOuterColor(0),
		animationStartOuterColor(0),
		animationEndOuterColor(0),
		animationOuterDuration(0.f),
		animationOuterDuraionRemain(0.f),
		animationOuterElapsedTime(0.f),
		animationOuterCurrentlyRate(0.f)
	{
		UUIDGenerator uuidGenerator;
		guid = uuidGenerator.GetGUID();
	}

	virtual void Update() = 0;
	virtual void Draw() = 0;

	void CheckGUID() { if (ObjectOverlapping::GetGUID() != guid) SetNoMouseWithClick(); }

	void SetInnerAnimationPoint(Color255 _start, Color255 _goal);
	void SetOuterAnimationPoint(Color255 _start, Color255 _goal);

	void UpdateInnerColor();
	void UpdateOuterColor();

	PosVec pos;
	PosVec size;

	bool enabled;

	bool mouseHit;
	bool mouseSelected;
	bool mouseClicked;
	bool beCalledNoMouse;

	std::string guid;

	Color255 currentInnerColor;
	Color255 currentOuterColor;

	bool animationInnerEnabled;
	bool animationOuterEnabled;

	Color255 animationStartInnerColor;
	Color255 animationEndInnerColor;
	Color255 animationStartOuterColor;
	Color255 animationEndOuterColor;
	float mInnerRed;
	float mInnerGreen;
	float mInnerBlue;
	float mOuterRed;
	float mOuterGreen;
	float mOuterBlue;

	float animationOuterDuration;
	float animationOuterDuraionRemain;
	float animationOuterElapsedTime;
	float animationOuterCurrentlyRate;

	float animationInnerDuration;
	float animationInnerDuraionRemain;
	float animationInnerElapsedTime;
	float animationInnerCurrentlyRate;

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
	bool SetInnerAnimation(float _duration) { animationInnerEnabled = true; animationInnerDuration = _duration; animationInnerDuraionRemain = _duration; animationInnerElapsedTime = 0.f; return true; }
	bool SetInnerAnimation() { animationInnerEnabled = false; return true; }

	bool SetOuterAnimation(float _duration) { animationOuterEnabled = true; animationOuterDuration = _duration; animationOuterDuraionRemain = _duration; animationOuterElapsedTime = 0.f; return true; }
	bool SetOuterAnimation() { animationOuterEnabled = false; return true; }

	// �e(����)�݈̂ړ�(��Βl)
	bool SetPos(PosVec _pos) { pos = _pos; return true; }

	// �I�u�W�F�N�g�ړ��n(�q�v�f�܂�)
	bool Move(PosVec _delta);

	// �q�v�f�o�^
	bool RegisterChildren(ObjectBase* _object) { children.push_back(_object); return true; }

	// �����ɎQ�Ɠn�����ꂽ��ʏ��Ȃǂ̍\���̂���ꂽ�������������H
};

