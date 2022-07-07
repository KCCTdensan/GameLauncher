#pragma once
#include "ObjectBase.h"
#include "TextAlign.h"
#include <string>

class TextObject :
    public ObjectBase
{
public:
    TextObject(PosVec _pos, PosVec _size, std::string _text, int _innerColor = 0, TextAlign _align = TextAlign::LEFT)
        : ObjectBase(_pos, _size), text(_text), innerColor(_innerColor), align(_align)
    {}

    TextObject()
        : ObjectBase(PosVec(), PosVec()), text(), innerColor(0), align(TextAlign::LEFT)
    {}

    // •¶šî•ñ“o˜^
    bool SetText(std::string _text) { text = _text; return true; }

    // Fî•ñ“o˜^“™
    bool SetInnerColor(int _innerColor) { innerColor = _innerColor; return true; }

    // XV•`‰æ
    void Collide() {}
    void Update();
    void Draw();

private:
    std::string text;
    int innerColor;
    TextAlign align;
};

