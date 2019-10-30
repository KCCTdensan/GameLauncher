#pragma once

#include "DxLib.h"
#include "MusicData.h"
#include <array>
#include <string>

using namespace std;

constexpr int MUSIC_MAX = 64;

//デフォでバックグラウンド+ループ再生

class MusicManager
{
public:
	MusicManager();

	int Set(wstring stg, wstring path);
	int Delete(wstring stg);
	int DeleteAll(wstring stg);

	int Play(wstring stg);
	int Replay(wstring stg);
	int Stop(wstring stg);

	bool GetPlaying();
	wstring GetPlayingName();
	int GetNowPosition();
	int GetTotalTime();
	int GetDoingOutput();

	int ChangeVolume(int num);

private:

	std::array<MusicData, MUSIC_MAX> music;
	wstring playingName;
	bool isPlaying;
	int playingHandle;
	bool doingOutput;
};

