#pragma once
#include "ObjectBase.h"
#include <vector>
#include "PlayData.h"

// 基底クラスのメソッドは一部正しく動作しない可能性がある
class PlayListObject :
    public ObjectBase
{
    PlayListObject(PosVec _pos, PosVec _size)
    {}

    PlayListObject()
    {}

    // 色有効化無効化
    bool SetEnabledListFill(bool _enabled) { listEnabledFill = _enabled; return true; }
    bool SetEnabledListFill() { return listEnabledFill; }
    bool SetEnabledListOutline(bool _enabled, float _outlineWidth = -1.f) { listEnabledOutline = _enabled; listOutlineWidth = _outlineWidth ? _outlineWidth <= 0.f : 0.f; return true; }
    // 判定用リターン
    bool SetEnabledListOutline() { return listEnabledOutline; }

private:
    Color255 listInnerColor;
    Color255 listOuterColor;

    Color255 listDisabledInnerColor;
    Color255 listDisabledOuterColor;

    float listOutlineWidth;

    bool listEnabledFill;
    bool listEnabledOutline;

    std::vector<PlayData*> lists;
};

