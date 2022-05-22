#pragma once
#include "PositionVector.h"
#include <vector>

class ObjectBase
{
protected:
	ObjectBase(PosVec _pos, PosVec _size)
		:pos(_pos), size(_size), enabled(true), mouseHit(false), mouseClicked(false), mouseSelected(false),
		children{} {}

	virtual void Update() = 0;
	virtual void Draw() = 0;

	PosVec pos;
	PosVec size;

	bool enabled;

	bool mouseHit;
	bool mouseSelected;
	bool mouseClicked;

private:
	std::vector<ObjectBase*> children;

public:
	bool SetEnabled(bool _enabled) { enabled = _enabled; return true; }
	bool SetEnabled() { return enabled; }

	// ��Ƀ��C�����d�Ȃ��Ă����ꍇ�̉�������
	bool SetNoMouse() { mouseHit = false; return true; }
	bool SetNoMouseWithClick() { mouseHit = false; mouseClicked = false; return true; }

	// �}�E�X���͉���(Selected�Ȃǂ̔C�ӂ̕����ɌĂяo����)
	bool SetMouseOff() { mouseClicked = false; mouseSelected = false; Update(); return true; }

	// �}�E�X����n�擾
	bool GetMouseHit() { return mouseHit; }
	bool GetMouseClicked() { return mouseClicked; }
	bool GetMouseSelected() { return mouseSelected; }

	// �I�u�W�F�N�g�ړ��n(�q�v�f�܂�)
	bool Move(PosVec _delta);

	// �q�v�f�o�^
	bool RegisterChildren(ObjectBase* _object) { children.push_back(_object); return true; }

	// �����ɎQ�Ɠn�����ꂽ��ʏ��Ȃǂ̍\���̂���ꂽ�������������H
};

