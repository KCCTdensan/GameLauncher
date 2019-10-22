#pragma once

#include "ObjectData.h"
#include "FontData.h"
#include "OperationData.h"
#include <string>
#include <array>
#include "DxLib.h"

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

enum OBJECT_TYPE
{
	BUTTON,
	PICTURE
};

enum VAR
{
	X,
	Y,
	SIZE_X,
	SIZE_Y,
	EFFECTIVE_FLAG,
	MOUSE_FLAG,
	ANIMATION_FLAG,
	ACTIVATION_FLAG,
	WRITING_FLAG,
	WRITING_X,
	WRITING_Y
};

class ObjectManager
{
public:
	ObjectManager();

	int		Set							(wstring stg, int x, int y, int sizeX, int sizeY, OBJECT_TYPE type);
	int		ColorSet					(wstring stg, bool outsideFlag, int outsideColor, int outsideSize, bool insideFlag, int insideColor); //�w�肵�Ȃ��ꍇNULL
	int		RoundnessSet				(wstring stg, bool flag, int size = NULL);
	int		WritingSet					(wstring stg, bool flag, wstring data);
	int		WritingFontSet				(wstring stg, int Font = 0, int size = 1, int Color = 0, int arrangementX = 0, int arrangementY = 0);
	int		WritingFontSetToHandle		(wstring stg, wstring handleName, int Color = 0, int arrangementX = 0, int arrangementY = 0);
	int		ImageChestSet				(wstring stg, bool flag, wstring PicPath = NULL, int setX = 0, int setY = 0); //FLAG�̎����� �܂��CsetX Y �̓I�u�W�F�N�g�̃X�^�[�g�n�_��0�Ƃ���
	int		ChangeVarInt				(wstring stg, VAR var, int num);
	int		ChangeVarBool				(wstring stg, VAR var, bool flag);
	int		GetVarInt					(wstring stg, VAR var);
	bool	GetVarBool					(wstring stg, VAR var);
	int		Delete						(wstring stg);
	int		DeleteAll					(void);
	
	int		HandleFontSet				(wstring stg, int font = 0, int size = 15);
	int		GetHandleFont				(wstring stg);
	int		DeleteHandleFont			(wstring stg);
	int		DeleteHandleFontAll			(void);

	void	Update						(void);
	void	Draw						(void);

private:

	std::array<ObjectData, OBJECT_MAX> object;
	std::array<FontData, FONT_HANDLE_MAX> fontData;
};

