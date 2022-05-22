#pragma once
#include "ObjectBase.h"
class CanvasObject :
    public ObjectBase
{
public:
    CanvasObject(PosVec _pos, PosVec _size = PosVec())
        : ObjectBase(_pos, _size), enabledOutline(false), outerColor(0), outlineWidth (0) {}

    // 更新描画
    void Collide() {};
    void Update();
    void Draw();

    // 色有効化無効化
    bool SetEnabledOutline(bool _enabled, float _outlineWidth = 1) { enabledOutline = _enabled; outlineWidth = (enabledOutline) ? _outlineWidth : 0; return true; }
    bool SetEnabledOutline() { return enabledOutline; }

    // 色情報登録等
    bool SetOutlineColor(int _outerColor, float _outlineWidth) { outerColor = _outerColor; outlineWidth = _outlineWidth; return true; }

private:
    int outerColor;
    float outlineWidth;

    bool enabledOutline;

};

