#pragma once
#include "Color255.h"
class ColorPreset
{
public:
	// システムボタン
	static Color255 systemButtonInner;
	static Color255 systemButtonHovered;
	static Color255 systemButtonClicked;
	static Color255 systemButtonSelected;
	static Color255 systemButtonHoveredOnClose;
	static Color255 systemButtonClickedOnClose;
	static Color255 systemButtonSelectedOnClose;

	// ヘッダー
	static Color255 headerBanner;

	static Color255 navLinksInner;
	static Color255 navLinksHovered;
	static Color255 navLinksClicked;
	static Color255 navLinksSelected;

	static Color255 navLinksOuter;
	static Color255 navLinksOuterMouse;

	static Color255 titleLogo;

	// メインシーン
	static Color255 bgColor;
	static Color255 transparent;
	static Color255 backGray;

	// タイル
	static Color255 tileInner;
	static Color255 tileHovered;
	static Color255 tileClicked;
	static Color255 tileSelected;
	static Color255 tileOuter;
	static Color255 tileOuterMouse;

	// 通常文字
	static Color255 textBlack;
	static Color255 textGray;
	static Color255 textObject;
	static Color255 textObjectWhite;

	// 黄色ボタン
	static Color255 yellowButtonInner;
	static Color255 yellowButtonHovered;
	static Color255 yellowButtonClicked;
	static Color255 yellowButtonSelected;
	static Color255 yellowButtonOuter;

	// インプットデフォルト
	static Color255 inputInner;
	static Color255 inputHovered;
	static Color255 inputClicked;
	static Color255 inputSelected;
	static Color255 inputOuter;
};

