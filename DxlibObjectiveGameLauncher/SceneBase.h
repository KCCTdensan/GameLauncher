#pragma once
#include <vector>
#include <string>
#include "FontChest.h"
#include "ObjectLayer.h"
#include "FontHandleData.h"

class SceneBase
{
public:
	SceneBase()
		: fonts(), layer(), canvases() {};
	~SceneBase();

	virtual void Collide() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	void RegFonts();

	// ポップアップウインドウを作る 引数にキャンバスを放り込む(キャンバスを親設定しておくと登録しない限り描画されない)
	void CreatePopUpWindow(ObjectBase* canvas);
	void DeletePopUpWindow(ObjectBase* canvas);

	std::vector<FontHandle> fonts;

	ObjectLayer layer;
	ObjectLayer canvases;
};

