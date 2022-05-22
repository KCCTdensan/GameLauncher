#pragma once
#include "ObjectBase.h"
class CanvasObject :
    public ObjectBase
{
public:
    CanvasObject(PosVec _pos, PosVec _size = PosVec())
        : ObjectBase(_pos, _size), enabledOutline(false), outerColor(0), outlineWidth (0) {}

    // XV•`‰æ
    void Collide() {};
    void Update();
    void Draw();

    // F—LŒø‰»–³Œø‰»
    bool SetEnabledOutline(bool _enabled, float _outlineWidth = 1) { enabledOutline = _enabled; outlineWidth = (enabledOutline) ? _outlineWidth : 0; return true; }
    bool SetEnabledOutline() { return enabledOutline; }

    // Fî•ñ“o˜^“™
    bool SetOutlineColor(int _outerColor, float _outlineWidth) { outerColor = _outerColor; outlineWidth = _outlineWidth; return true; }

private:
    int outerColor;
    float outlineWidth;

    bool enabledOutline;

};

