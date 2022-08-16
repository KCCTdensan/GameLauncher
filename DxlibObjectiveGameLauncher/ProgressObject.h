#pragma once
#include "ObjectBase.h"
#include "ButtonObject.h"

class ProgressObject :
    public ObjectBase
{
public:
    // 0~1
    ProgressObject(PosVec _pos, PosVec _size, bool _verticalMode = true, float _initialValue = 0.f)
        : ObjectBase(_pos, _size),
        enabledFill(true), enabledOutline(false), outlineWidth(0.f), verticalMode(_verticalMode), value(_initialValue)
    {
        float initialValue = _initialValue;
        if (initialValue < 0.f) initialValue = 0.f;
        else if (initialValue > 1.f) initialValue = 1.f;
        if (verticalMode)
            slider = ButtonObject(PosVec(pos.x, pos.y), PosVec(size.x, size.y * initialValue), true, false);
        else
            slider = ButtonObject(PosVec(pos.x, pos.y), PosVec(size.x * initialValue, size.y), true, false);
        expandedNum = true;
    }

    ProgressObject()
        : ObjectBase(PosVec(), PosVec()),
        enabledFill(true), enabledOutline(false), outlineWidth(0.f), verticalMode(true), value(0.f) {}

    // 色有効化無効化
    bool SetEnabledFill(bool _enabled) { enabledFill = _enabled; return true; }
    bool SetEnabledFill() { return enabledFill; }
    bool SetEnabledOutline(bool _enabled, float _outlineWidth = -1.f) { enabledOutline = _enabled; outlineWidth = _outlineWidth ? _outlineWidth <= 0.f : 0.f; return true; }
    
    void SetupSlider();

    // 判定用リターン
    bool SetEnabledOutline() { return enabledOutline; }

    // 色情報登録等
    bool SetInnerColor(Color255 _innerColor, bool _defaultFill = true)
    {
        innerColor = _innerColor;
        hoveredInnerColor = _innerColor;
        clickedInnerColor = _innerColor;
        selectedInnerColor = _innerColor;
        if (_defaultFill) {
            innerAnimation.current = innerColor;
            innerAlphaAnimation.current = (float)innerColor.a;
        }
        return true;
    }
    bool SetInnerColor(Color255 _innerColor, Color255 _hoveredColor, Color255 _clickedColor, Color255 _selectedColor, bool _defaultFill = true)
    {
        innerColor = _innerColor;
        hoveredInnerColor = _hoveredColor;
        clickedInnerColor = _clickedColor;
        selectedInnerColor = _selectedColor;
        if (_defaultFill) {
            innerAnimation.current = innerColor;
            innerAlphaAnimation.current = (float)innerColor.a;
        }
        return true;
    }
    // アウトラインを表示する際はtrueになっているかをチェック
    bool SetOutlineColor(Color255 _outerColor, float _outlineWidth, bool _defaultFill = true) {
        outerColor = _outerColor;
        hoveredOuterColor = _outerColor;
        clickedOuterColor = _outerColor;
        selectedOuterColor = _outerColor;
        outlineWidth = _outlineWidth;
        if (_defaultFill) {
            outerAnimation.current = outerColor;
            outerAlphaAnimation.current = (float)outerColor.a;
        }
        return true;
    }
    // アウトラインを表示する際はtrueになっているかをチェック
    bool SetOutlineColor(Color255 _outerColor, Color255 _hoveredColor, Color255 _clickedColor, Color255 _selectedColor, float _outlineWidth, bool _defaultFill = true) {
        outerColor = _outerColor;
        hoveredOuterColor = _hoveredColor;
        clickedOuterColor = _clickedColor;
        selectedOuterColor = _selectedColor;
        outlineWidth = _outlineWidth;
        if (_defaultFill) {
            outerAnimation.current = outerColor;
            outerAlphaAnimation.current = (float)outerColor.a;
        }
        return true;
    }

    Color255* GetColor(ColorType type) {
        switch (type)
        {
        case ColorType::INNER:
            return &innerColor;
        case ColorType::HOVERED:
            return &hoveredInnerColor;
        case ColorType::CLICKED:
            return &clickedInnerColor;
        case ColorType::SELECTED:
            return &selectedInnerColor;
        case ColorType::OUTER_INNER:
            return &outerColor;
        case ColorType::OUTER_HOVERED:
            return &hoveredOuterColor;
        case ColorType::OUTER_CLICKED:
            return &clickedOuterColor;
        case ColorType::OUTER_SELECTED:
            return &selectedOuterColor;
        default:
            return nullptr;
        }
    }

    // 移動系の操作は非推奨
    ButtonObject* GetSlider() { return &slider; }

    float GetValue() { return value; }
    void SetValue(float _value) { 
        value = _value;
        if (value < 0.f) value = 0.f;
        else if (value > 1.f) value = 1.f;
        if (verticalMode) {
            slider.SetSize(PosVec(slider.GetSize().x, value * size.y));
        }
        else {
            slider.SetSize(PosVec(value * size.x, slider.GetSize().y));
        }
    }

    // 更新描画
    void Collide() override;
    void Update() override;
    void Draw() override;

private:

    void CollideMouse() override;

private:
    Color255 innerColor;
    Color255 hoveredInnerColor;
    Color255 clickedInnerColor;
    Color255 selectedInnerColor;
    Color255 outerColor;
    Color255 hoveredOuterColor;
    Color255 clickedOuterColor;
    Color255 selectedOuterColor;

    bool enabledFill;
    bool enabledOutline;

    float outlineWidth;

    float value;

    bool verticalMode;

    ButtonObject slider;

    // スライダークリック時に登録
    PosVec clickedPos;
};

