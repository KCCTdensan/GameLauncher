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

	int Set(string stg, string path);
	int Delete(string stg);
	int DeleteAll();

	int Play(string stg);
	int Replay(string stg);
	int Stop(string stg);

	bool GetPlaying();
	string GetPlayingName();
	int GetNowPosition();
	int GetTotalTime();
	int GetDoingOutput();

	int ChangeVolume(int num);

private:

	std::array<MusicData, MUSIC_MAX> music;
	string playingName;
	bool isPlaying;
	int playingHandle;
	bool doingOutput;
};

