#pragma once
#include "ObjectBase.h"
#include "DxLib.h"

class ButtonObject :
    public ObjectBase
{
public:
    ButtonObject(float _x, float _y, float _sx, float _sy, int _innerColor, int _outerColor, int _hoveredColor, int _clickedColor, int _selectedColor)
        : ObjectBase(_x, _y, _sx, _sy, _innerColor, _outerColor) {
        hoveredColor = _hoveredColor;
        clickedColor = _clickedColor;
        selectedColor = _selectedColor;
    }

    void Update();
    void Draw();

private:
    int hoveredColor;
    int clickedColor;
    int selectedColor;
};

