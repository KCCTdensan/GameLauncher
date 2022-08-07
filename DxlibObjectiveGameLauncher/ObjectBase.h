#pragma once
#include "PositionVector.h"
#include "UUIDGenerator.h"
#include "ObjectOverlapping.h"
#include "ApplicationTime.h"
#include "Color255.h"
#include "AnimationStatus.h"
#include <vector>

class ObjectBase
{
protected:
	ObjectBase(PosVec _pos, PosVec _size)
		:pos(_pos), size(_size),
		enabled(true), mouseHit(false), mouseClicked(false), mouseSelected(false),
		children{}, beCalledNoMouse(false), guid(),
		innerAnimation(AnimationColorStatus()),
		outerAnimation(AnimationColorStatus())
	{
		UUIDGenerator uuidGenerator;
		guid = uuidGenerator.GetGUID();
	}

	virtual void Update() = 0;
	virtual void Draw() = 0;

	void CheckGUID() { if (ObjectOverlapping::GetGUID() != guid) SetNoMouseWithClick(); }

	void SetAnimationColorPoint(AnimationColorStatus& type, Color255 _start, Color255 _goal);
	void UpdateAnimationColor(AnimationColorStatus& type);

	void SetAnimationPoint(AnimationStatus& type, int _start, int _goal);
	void UpdateAnimation(AnimationStatus& type);

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

private:
	std::vector<ObjectBase*> children;

public:
	bool SetEnabled(bool _enabled) { enabled = _enabled; return true; }
	bool SetEnabled() { return enabled; }

	// 上にレイヤが重なっていた場合の解除処理
	bool SetNoMouse() { mouseHit = false; return true; }
	bool SetNoMouseWithClick() { mouseHit = false; mouseClicked = false; /*beCalledNoMouse = true;*/ return true; }

	// マウス入力解除(Selectedなどの任意の分岐後に呼び出し等)
	bool SetMouseOff() { mouseClicked = false; mouseSelected = false; return true; }

	// マウス判定系取得
	bool GetMouseHit() { return mouseHit; }
	bool GetMouseClicked() { return mouseClicked; }
	bool GetMouseSelected() { return mouseSelected; }

	// アニメーション設定
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

	// 親(自分)のみ移動(絶対値)
	bool SetPos(PosVec _pos) { pos = _pos; return true; }

	// オブジェクト移動系(子要素含む)
	bool Move(PosVec _delta);

	// 子要素登録
	bool RegisterChildren(ObjectBase* _object) { children.push_back(_object); return true; }

	// ここに参照渡しされた画面情報などの構造体を入れた方がいいかも？
};

