#pragma once
#include "ObjectBase.h"
#include <vector>
#include "PlayData.h"
#include "ButtonObject.h"

// 基底クラスのメソッドは一部正しく動作しない可能性がある
class PlayListObject :
    public ObjectBase
{
public:
    PlayListObject(PosVec _pos, PosVec _size)
        : ObjectBase(_pos, _size), listSample(nullptr),
        listInnerColor(0), listOuterColor(0), listDisabledInnerColor(0), listDisabledOuterColor(0),
        listEnabledFill(true), listEnabledOutline(true), listOutlineWidth(false), listHeight(50.f)
    {}

    PlayListObject()
    {}

    // 色有効化無効化
    bool SetEnabledListFill(bool _enabled) { listEnabledFill = _enabled; return true; }
    bool SetEnabledListFill() { return listEnabledFill; }
    bool SetEnabledListOutline(bool _enabled, float _outlineWidth = -1.f) { listEnabledOutline = _enabled; listOutlineWidth = _outlineWidth ? _outlineWidth <= 0.f : 0.f; return true; }
    // 判定用リターン
    bool SetEnabledListOutline() { return listEnabledOutline; }

    // 色情報登録等
    bool SetInnerColor(Color255 _innerColor, bool _defaultFill = true)
    {
        innerColor = _innerColor;
        if (_defaultFill) {
            innerAnimation.current = innerColor;
            innerAlphaAnimation.current = (float)innerColor.a;
        }
        listDisabledInnerColor = Color255(innerColor.r, innerColor.g, innerColor.b, (int)(innerColor.a / 5));
        return true;
    }
    // アウトラインを表示する際はtrueになっているかをチェック
    bool SetOutlineColor(Color255 _outerColor, float _outlineWidth, bool _defaultFill = true) {
        outerColor = _outerColor;
        listOutlineWidth = _outlineWidth;
        if (_defaultFill) {
            outerAnimation.current = outerColor;
            outerAlphaAnimation.current = (float)outerColor.a;
        }
        listDisabledOuterColor = Color255(outerColor.r, outerColor.g, outerColor.b, (int)(outerColor.a / 5));
        return true;
    }

    ButtonObject* GetButtonListSample() { return listSample; }
    ButtonObject* SetButtonListSample(ButtonObject* sample) { listSample = sample; }

    bool SetListHeight(float _height) { listHeight = _height; return false; }

    bool SetList(std::vector<PlayData> playLists);

    // 更新描画
    void Collide() override;
    void Update() override;
    void Draw() override;

private:

    void CollideMouse() override {}

private:

    Color255 listInnerColor;
    Color255 listOuterColor;

    Color255 listDisabledInnerColor;
    Color255 listDisabledOuterColor;

    Color255 innerColor;
    Color255 outerColor;

    float listOutlineWidth;

    bool listEnabledFill;
    bool listEnabledOutline;

    float listHeight;

    ButtonObject* listSample;

    std::vector<PlayData> lists;
    std::vector<ButtonObject*> buttons;
};

