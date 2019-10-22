#pragma once

#include "DxLib.h"
#include "MusicData.h"
#include <array>
#include <string>

using namespace std;

constexpr int MUSIC_MAX = 64;

//�f�t�H�Ńo�b�N�O���E���h+���[�v�Đ�

class MusicManager
{
public:
	MusicManager();

	int Set(wstring stg, wstring path);
	int Delete(wstring stg);
	int DeleteAll(wstring stg);

	int Play(wstring stg);
	int RePlay(wstring stg);
	int Stop(wstring stg);

	int ChangeVolume(int num);

private:

	std::array<MusicData, MUSIC_MAX> music;
};
