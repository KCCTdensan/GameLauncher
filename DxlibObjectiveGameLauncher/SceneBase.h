#pragma once
#include <vector>
#include <string>
#include "FontChest.h"
#include "ObjectLayer.h"
#include "FontHandleData.h"

struct SharingScenes;

class SceneBase
{
public:
	SceneBase(SharingScenes* _sharingScenes)
		: fonts(), layer(), canvases(), sharingScenes(_sharingScenes) {};
	SceneBase()
		: fonts(), layer(), canvases(), sharingScenes(nullptr) {};
	~SceneBase();

	virtual void Collide() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	void RegFonts();

	// �|�b�v�A�b�v�E�C���h�E����� �����ɃL�����o�X����荞��(�L�����o�X��e�ݒ肵�Ă����Ɠo�^���Ȃ�����`�悳��Ȃ�)
	void CreatePopUpWindow(ObjectBase* canvas);
	void DeletePopUpWindow(ObjectBase* canvas);

	std::vector<FontHandle> fonts;

	ObjectLayer layer;
	ObjectLayer canvases;

	// �|�b�v�A�b�v�Z�b�g�����(�\���̂�)

	ObjectLayer pCanvases;
	ObjectLayer pLayer;

	SharingScenes* sharingScenes;
};

