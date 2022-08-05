#pragma once

#include "ObjectData.h"
#include "FontData.h"
#include "OperationData.h"
#include <string>
#include <array>
#include "DxLib.h"
#include "ObjectEnum.h"

constexpr int OBJECT_MAX = 256;
constexpr int FONT_HANDLE_MAX = 256;

constexpr int ARRANGEMENT_X_LEFT = 1;
constexpr int ARRANGEMENT_X_CENTER = 0;
constexpr int ARRANGEMENT_X_RIGHT = 2;

constexpr int ARRANGEMENT_Y_TOP = 1;
constexpr int ARRANGEMENT_Y_CENTER = 0;
constexpr int ARRANGEMENT_Y_BOTTOM = 2;

constexpr int OBJECT_FONT_GOTHIC = 0;

constexpr int OBJECT_BUTTON = 0;
constexpr int OBJECT_INPUT = 1;


using namespace std;

class ObjectManager
{
public:
	ObjectManager();

	int		Set							(string str, int x, int y, int sizeX, int sizeY, OBJECT_TYPE type);
	int		ColorSet					(string str, bool outsideFlag, int outsideColor, int outsideSize, bool insideFlag, int insideColor); //指定しない場合NULL
	int		RoundnessSet				(string str, bool flag, int size = NULL);
	int		WritingSet					(string str, bool flag, string data);
	int		WritingFontSet				(string str, int Font = 0, int size = 1, int Color = 0, int arrangementX = 0, int arrangementY = 0);
	int		WritingFontSetToHandle		(string str, string handleName, int Color = 0, int arrangementX = 0, int arrangementY = 0);
	int		ImageChestSet				(string str, bool flag, string PicPath = NULL, int setX = 0, int setY = 0); //FLAGの時も可 また，setX Y はオブジェクトのスタート地点を0とする
	int		ProgressSet					(string str, bool flag, int frontColor, int backColor, float startRate = 0.0f);
	int		ChangeProgress				(string str, float rate);
	int		ChangeVarInt				(string str, VAR var, int num);
	int		ChangeVarBool				(string str, VAR var, bool flag);
	int		GetVarInt					(string str, VAR var);
	bool	GetVarBool					(string str, VAR var);
	int		Delete						(string str);
	int		DeleteAll					(void);
	
	int		HandleFontSet				(string str, int font = 0, int size = 15);
	int		GetHandleFont				(string str);
	int		DeleteHandleFont			(string str);
	int		DeleteHandleFontAll			(void);

	void	Update						(void);
	void	Draw						(void);

private:

	void	ArrangementSet				(int num);

	std::array<ObjectData, OBJECT_MAX> object;
	std::array<FontChest, FONT_HANDLE_MAX> fontData;

	int latestClick = 0;
};

