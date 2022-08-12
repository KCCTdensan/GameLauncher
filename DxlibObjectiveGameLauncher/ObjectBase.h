#pragma once
#include "PositionVector.h"
#include "UUIDGenerator.h"
#include "ObjectOverlapping.h"
#include "ApplicationTime.h"
#include "Color255.h"
#include "AnimationStatus.h"
#include "ApplicationPreference.h"
#include "AnimationPointerData.h"
#include "ColorTypes.h"
#include "VectorTypes.h"
#include "MouseEventCase.h"
#include <vector>

class ObjectBase
{
protected:
	ObjectBase(PosVec _pos, PosVec _size)
		:pos(_pos), size(_size),
		enabled(true), mouseHit(false), mouseClicked(false), mouseSelected(false),
		children{}, beCalledNoMouse(false), guid(), canvasOwner(false), canvasId(-1),
		innerAnimation(AnimationColorStatus()),
		outerAnimation(AnimationColorStatus()),
		innerAlphaAnimation(AnimationStatus()),
		outerAlphaAnimation(AnimationStatus()),
		parent(nullptr)
	{
		UUIDGenerator uuidGenerator;
		guid = uuidGenerator.GetGUID();
	}

	void CheckGUID() { if (ObjectOverlapping::GetGUID() != guid) SetNoMouseWithClick(); }

	void SetAnimationColorPoint(AnimationColorStatus* type, Color255 _start, Color255 _goal);
	void UpdateAnimationColor(AnimationColorStatus* type);

	void SetAnimationPoint(AnimationStatus* type, float _start, float _goal);
	void UpdateAnimation(AnimationStatus* type);
	
	void UpdatePointerAnimation();

	PosVec pos;
	PosVec size;

	bool enabled;

	bool mouseHit;
	bool mouseSelected;
	bool mouseClicked;
	bool beCalledNoMouse;

	std::string guid;

	AnimationColorStatus innerAnimation;
	AnimationColorStatus outerAnimation;
	AnimationStatus innerAlphaAnimation;
	AnimationStatus outerAlphaAnimation;

	int canvasId;
	bool canvasOwner;
	std::vector<ObjectBase*> children;
	ObjectBase* parent;

private:
	std::vector<AnimationColorPointer> pColorAnimation;
	std::vector<AnimationPointer> pAnimation;

public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Collide() = 0;

	PosVec GetPos() { return pos; }
	PosVec GetSize() { return size; }

	PosVec* GetVectorPointer(VectorType type) {
		switch (type)
		{
		case VectorType::POS:
			return &pos;
		case VectorType::SIZE:
			return &size;
		default:
			return nullptr;
		}
	}

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

	void ChangeColorWithAnimation(Color255* pColor, Color255* endColor, float duration);
	void ChangeValueWithAnimation(float* pValue, float endValue, float duration);

	void SetCanvasId(int id);

	// �A�j���[�V�����ݒ�
	bool SetInnerAnimation(float _duration) {
		innerAnimation.animationEnabled = true;
		innerAnimation.duration = _duration;
		innerAnimation.durationRemain = _duration;
		innerAnimation.elapsedTime = 0.f;
		innerAlphaAnimation.animationEnabled = true;
		innerAlphaAnimation.duration = _duration;
		innerAlphaAnimation.durationRemain = _duration;
		innerAlphaAnimation.elapsedTime = 0.f;
		return true;
	}
	bool SetInnerAnimation() {
		innerAnimation.animationEnabled = false;
		innerAlphaAnimation.animationEnabled = false;
		return true; }

	bool SetOuterAnimation(float _duration) {
		outerAnimation.animationEnabled = true;
		outerAnimation.duration = _duration;
		outerAnimation.durationRemain = _duration;
		outerAnimation.elapsedTime = 0.f;
		outerAlphaAnimation.animationEnabled = true;
		outerAlphaAnimation.duration = _duration;
		outerAlphaAnimation.durationRemain = _duration;
		outerAlphaAnimation.elapsedTime = 0.f;
		return true;
	}
	bool SetOuterAnimation() {
		outerAnimation.animationEnabled = false;
		outerAlphaAnimation.animationEnabled = false;
		return true;
	}

	// �e(����)�݈̂ړ�(��Βl)
	bool SetPos(PosVec _pos) { pos = _pos; return true; }

	// �I�u�W�F�N�g�ړ��n(�q�v�f�܂�)
	bool Move(PosVec _delta);

	// �q�v�f�o�^
	virtual bool RegisterChildren(ObjectBase* _object) { children.push_back(_object); return true; }
	// �����̃|�C���^����荞�ނ悤��(�L�����o�X�p)
	virtual bool RegisterParent(ObjectBase* _object) { parent = _object; return true; }

	// �����ɎQ�Ɠn�����ꂽ��ʏ��Ȃǂ̍\���̂���ꂽ�������������H
};

