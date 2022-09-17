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
#include "MouseInput.h"
#include <vector>

/// <summary>
/// <para>�I�u�W�F�N�g��ݒu����ۂ̊�{�ƂȂ钊�ۃN���X�B���̃N���X�P�̂ł̓C���X�^���X���ł��Ȃ��̂Œ��ӁB</para>
/// <para>�����̃I�u�W�F�N�g�̎�ނ�1�ɂ܂Ƃ߂Ĕz�񉻂��������ɂ͌^����ObjectBase*�ɂ��邱�Ƃ𐄏��B</para>
/// </summary>
/// <param name="_pos">�I�u�W�F�N�g�̍�����W(2����)</param>
/// <param name="_size">�I�u�W�F�N�g�̑傫��(2����)</param>
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
		parent(nullptr), enforcedCollision(1),
		expandedNum(false), imageHandle(-1), enforcedHovered(false), enforcedClicked(false), enforcedSelected(false)
	{
		UUIDGenerator uuidGenerator;
		guid = uuidGenerator.GetGUID();
	}

	ObjectBase()
		:pos(PosVec()), size(PosVec()),
		enabled(true), mouseHit(false), mouseClicked(false), mouseSelected(false),
		children{}, beCalledNoMouse(false), guid(), canvasOwner(false), canvasId(-1),
		innerAnimation(AnimationColorStatus()),
		outerAnimation(AnimationColorStatus()),
		innerAlphaAnimation(AnimationStatus()),
		outerAlphaAnimation(AnimationStatus()),
		parent(nullptr), enforcedCollision(1),
		expandedNum(false), imageHandle(-1), enforcedHovered(false), enforcedClicked(false), enforcedSelected(false)
	{
		UUIDGenerator uuidGenerator;
		guid = uuidGenerator.GetGUID();
	}

	void CheckGUID() { if (ObjectOverlapping::GetGUID() != guid) SetNoMouseWithClick(); } // �I�u�W�F�N�g�d�Ȃ蔻��ɂ����Ĉ�ԏ�ł͂Ȃ������ꍇ�I������������(�����Ăяo��)
	void UpdateEnforcedMouseCollision();

	void SetAnimationColorPoint(AnimationColorStatus* type, Color255 _start, Color255 _goal); // �A�j���[�V�����J���[�����ݒ�
	void UpdateAnimationColor(AnimationColorStatus* type); // SetAnimationColorPoint()�Őݒ肳�ꂽ�l�̍X�V����(�����Ăяo��)

	void SetAnimationPoint(AnimationStatus* type, float _start, float _goal); // �A�j���[�V���������ݒ�
	void UpdateAnimation(AnimationStatus* type); // SetAnimationPoint()�Őݒ肳�ꂽ�l�̍X�V����(�����Ăяo��)
	
	void UpdatePointerAnimation(); // pColorAnimation, pAnimation�ɒǉ����ꂽ(���W�n���X)�̃p�����[�^�̍X�V����(�����Ăяo��)

	void CollideMouseAsBox(); // �����蔻�肪��`�̏ꍇ�͂����p���邱�Ƃ𐄏�����

	PosVec pos; // ������W
	PosVec size; // �傫��

	bool enabled; // �L�����(false���͔���C�X�V��������{�Ȃ�)

	bool mouseHit; // �}�E�X�z�o�[��
	bool mouseSelected; // �}�E�X���A�N�e�B�u�Ȏ�
	bool mouseClicked; // �}�E�X���I�u�W�F�N�g��ŃN���b�N���ꂽ��
	bool beCalledNoMouse;

	bool expandedNum; // �����蔻����N���b�N���Ɋg�����邩

	std::string guid; // ���ʃR�[�h(�����p���ďd��������s��)

	AnimationColorStatus innerAnimation; // �����F�A�j���[�V�����\����
	AnimationColorStatus outerAnimation; // �O���F�A�j���[�V�����\����
	AnimationStatus innerAlphaAnimation; // �������߃A�j���[�V�����\����
	AnimationStatus outerAlphaAnimation; // �O�����߃A�j���[�V�����\����

	int canvasId; // �L�����o�X�̃n���h��
	bool canvasOwner; // True�̏ꍇ�CcanvasId�͎��g�̃n���h���Ƃ��Ĉ�����(CanvasObject���ɗL��)
	std::vector<ObjectBase*> children; // �q�I�u�W�F�N�g(�Ǐ]�Ȃǂ��\�ɂȂ�)
	ObjectBase* parent; // �e�����̐ݒ�(Canvas��ݒ肷��Ɠ����蔻��Ȃǂ𓾂邱�Ƃ��o����悤�ɂȂ�)

	int enforcedCollision; // �����蔻��ŗD�揇�ʂ�����ꍇ�C�����p����(���p�֎~)

	int imageHandle; // �摜�n���h�� (�����擾�����͂��Ȃ����߁C���炩���߃n���h���𓾂Ă����K�v������)
	PosVec imageOffset; // pos����w��ʂ����摜�̍�����W�𓮂���
	PosVec imageSize; // �ڕW�T�C�Y(�g��k�������)
	double imageAngle; // �摜�̉�]�p(���W�A��)
	bool imageTurnFlagX; // X�����ɔ��]���邩
	bool imageTurnFlagY; // Y�����ɔ��]���邩
	PosVec imageCenter; // ��]�̒��S

	AnimationStatus imageAlphaAnimation;

	Color255 defaultImageColor;
	Color255 hoveredImageColor;
	Color255 clickedImageColor;
	Color255 selectedImageColor;

	Color255 disabledImageColor;

private:

	virtual void CollideMouse() = 0; // �}�E�X���菈��

private:
	std::vector<AnimationColorPointer> pColorAnimation;
	std::vector<AnimationPointer> pAnimation;
	std::vector<AnimationPointerInt> pAnimationInt;

	bool enforcedHovered;
	bool enforcedClicked;
	bool enforcedSelected;

public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Collide() = 0;

	PosVec GetPos() { return pos; }
	PosVec GetLocalPos();
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

	bool GetCanvasOwner() { return canvasOwner; }
	int GetCanvasId() { return canvasId; }

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

	void SetMouseHit(bool flag) { enforcedHovered = flag; }
	void SetMouseClicked(bool flag) { enforcedClicked = flag; }
	void SetMouseSelected(bool flag) { enforcedSelected = flag; }

	void ChangeColorWithAnimation(Color255* pColor, Color255* endColor, float duration);
	void ChangeValueWithAnimation(float* pValue, float endValue, float duration);
	void ChangeValueWithAnimation(int* pValue, int endValue, float duration);

	void SetCanvasId(int id);

	void SetImageHandle(int handle = -1) { imageHandle = handle; }

	void SetImageOffsrt(PosVec offset) { imageOffset = offset; }
	void SetImageSize(PosVec size) { imageSize = size; }
	void SetImageAngle(double angle) { imageAngle = angle; }
	void SetImageTurnFlag(bool turnX = false, bool turnY = false) { imageTurnFlagX = turnX; imageTurnFlagY = turnY; }
	void SetImageCenter(PosVec center) { imageCenter = center; }

	void SetEnforcedCollision(int _enforcedCollision = 1) { enforcedCollision = _enforcedCollision; }

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
		imageAlphaAnimation.animationEnabled = true;
		imageAlphaAnimation.duration = _duration;
		imageAlphaAnimation.durationRemain = _duration;
		imageAlphaAnimation.elapsedTime = 0.f;
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

	// alpha�l�̂ݓK�p�����
	bool SetImageAlpha(Color255 _alpha) {
		defaultImageColor = _alpha;
		hoveredImageColor = _alpha;
		clickedImageColor = _alpha;
		selectedImageColor = _alpha;
		imageAlphaAnimation.current = (float)defaultImageColor.a;

		disabledImageColor = Color255(0, _alpha.a);

		return true;
	}

	// alpha�l�̂ݓK�p�����
	bool SetImageAlpha(Color255 _alpha, Color255 _hoveredColor, Color255 _clickedColor, Color255 _selectedColor) {
		defaultImageColor = _alpha;
		hoveredImageColor = _hoveredColor;
		clickedImageColor = _clickedColor;
		selectedImageColor = _selectedColor;
		imageAlphaAnimation.current = (float)defaultImageColor.a;

		disabledImageColor = Color255(0, _alpha.a);

		return true;
	}

	// �e(����)�݈̂ړ�(��Βl)
	bool SetPos(PosVec _pos) { pos = _pos; return true; }
	void SetLocalPos(PosVec _localPos);

	bool SetSize(PosVec _size) { size = _size; return true; }

	// �I�u�W�F�N�g�ړ��n(�q�v�f�܂�)
	virtual bool Move(PosVec _delta, bool _involvedParent = true);

	// �q�v�f�o�^
	virtual bool RegisterChildren(ObjectBase* _object);
	// �����̃|�C���^����荞�ނ悤��(�L�����o�X�p)(�`��挈��p) ��children�̊֐����ĂԂ��ߗ\��RegisterChildren���K�v
	virtual bool RegisterParent(ObjectBase* _object);
};

