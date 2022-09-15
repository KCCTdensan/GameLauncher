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
/// <para>オブジェクトを設置する際の基本となる抽象クラス。このクラス単体ではインスタンス化できないので注意。</para>
/// <para>複数のオブジェクトの種類を1つにまとめて配列化したい時には型名をObjectBase*にすることを推奨。</para>
/// </summary>
/// <param name="_pos">オブジェクトの左上座標(2次元)</param>
/// <param name="_size">オブジェクトの大きさ(2次元)</param>
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
		expandedNum(false), imageHandle(-1)
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
		expandedNum(false), imageHandle(-1)
	{
		UUIDGenerator uuidGenerator;
		guid = uuidGenerator.GetGUID();
	}

	void CheckGUID() { if (ObjectOverlapping::GetGUID() != guid) SetNoMouseWithClick(); } // オブジェクト重なり判定において一番上ではなかった場合選択を解除する(推奨呼び出し)

	void SetAnimationColorPoint(AnimationColorStatus* type, Color255 _start, Color255 _goal); // アニメーションカラー初期設定
	void UpdateAnimationColor(AnimationColorStatus* type); // SetAnimationColorPoint()で設定された値の更新処理(推奨呼び出し)

	void SetAnimationPoint(AnimationStatus* type, float _start, float _goal); // アニメーション初期設定
	void UpdateAnimation(AnimationStatus* type); // SetAnimationPoint()で設定された値の更新処理(推奨呼び出し)
	
	void UpdatePointerAnimation(); // pColorAnimation, pAnimationに追加された(座標系等々)のパラメータの更新処理(推奨呼び出し)

	void CollideMouseAsBox(); // 当たり判定が矩形の場合はこれを用いることを推奨する

	PosVec pos; // 左上座標
	PosVec size; // 大きさ

	bool enabled; // 有効状態(false時は判定，更新処理が基本ない)

	bool mouseHit; // マウスホバー時
	bool mouseSelected; // マウスがアクティブな時
	bool mouseClicked; // マウスがオブジェクト上でクリックされた時
	bool beCalledNoMouse;

	bool expandedNum; // 当たり判定をクリック時に拡張するか

	std::string guid; // 識別コード(これを用いて重複判定を行う)

	AnimationColorStatus innerAnimation; // 内側色アニメーション構造体
	AnimationColorStatus outerAnimation; // 外側色アニメーション構造体
	AnimationStatus innerAlphaAnimation; // 内側透過アニメーション構造体
	AnimationStatus outerAlphaAnimation; // 外側透過アニメーション構造体

	int canvasId; // キャンバスのハンドル
	bool canvasOwner; // Trueの場合，canvasIdは自身のハンドルとして扱われる(CanvasObject時に有効)
	std::vector<ObjectBase*> children; // 子オブジェクト(追従などが可能になる)
	ObjectBase* parent; // 親属性の設定(Canvasを設定すると当たり判定などを得ることが出来るようになる)

	int enforcedCollision; // 当たり判定で優先順位をつける場合，これを用いる(乱用禁止)

	int imageHandle; // 画像ハンドル (自動取得処理はしないため，あらかじめハンドルを得ておく必要がある)
	PosVec imageOffset; // posから指定量だけ画像の左上座標を動かす
	PosVec imageSize; // 目標サイズ(拡大縮小される)
	double imageAngle; // 画像の回転角(ラジアン)
	bool imageTurnFlagX; // X方向に反転するか
	bool imageTurnFlagY; // Y方向に反転するか
	PosVec imageCenter; // 回転の中心

private:

	virtual void CollideMouse() = 0; // マウス判定処理

private:
	std::vector<AnimationColorPointer> pColorAnimation;
	std::vector<AnimationPointer> pAnimation;

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

	// 上にレイヤが重なっていた場合の解除処理
	bool SetNoMouse() { mouseHit = false; return true; }
	bool SetNoMouseWithClick() { mouseHit = false; mouseClicked = false; /*beCalledNoMouse = true;*/ return true; }

	// マウス入力解除(Selectedなどの任意の分岐後に呼び出し等)
	bool SetMouseOff() { mouseClicked = false; mouseSelected = false; return true; }

	// マウス判定系取得
	bool GetMouseHit() { return mouseHit; }
	bool GetMouseClicked() { return mouseClicked; }
	bool GetMouseSelected() { return mouseSelected; }

	void ChangeColorWithAnimation(Color255* pColor, Color255* endColor, float duration);
	void ChangeValueWithAnimation(float* pValue, float endValue, float duration);

	void SetCanvasId(int id);

	void SetImageHandle(int handle = -1) { imageHandle = handle; }

	void SetImageOffsrt(PosVec offset) { imageOffset = offset; }
	void SetImageSize(PosVec size) { imageSize = size; }
	void SetImageAngle(double angle) { imageAngle = angle; }
	void SetImageTurnFlag(bool turnX = false, bool turnY = false) { imageTurnFlagX = turnX; imageTurnFlagY = turnY; }
	void SetImageCenter(PosVec center) { imageCenter = center; }

	void SetEnforcedCollision(int _enforcedCollision = 1) { enforcedCollision = _enforcedCollision; }

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
	void SetLocalPos(PosVec _localPos);

	bool SetSize(PosVec _size) { size = _size; return true; }

	// オブジェクト移動系(子要素含む)
	virtual bool Move(PosVec _delta, bool _involvedParent = true);

	// 子要素登録
	virtual bool RegisterChildren(ObjectBase* _object);
	// 自分のポインタを放り込むように(キャンバス用)(描画先決定用) ※childrenの関数を呼ぶため予めRegisterChildrenが必要
	virtual bool RegisterParent(ObjectBase* _object);
};

