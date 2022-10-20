#pragma once
#include "MusicChest.h" // 現状Deleteするため
#include <vector>
#include "PlayData.h"
#include "PlayState.h"
#include <random>

class MusicPlayer
{
public:
	static void PlayInList(PlayState playState, int index, bool playAtStart = false);
	static void StopInList();

	static PlayData GetPlayingData();
	static PlayData GetPlayNextData(int offset = 1);
	static float GetPlayingRate();
	static int GetPlayingIndex() { return playingIndex; }
	static bool GetPlaying() { return playing; }

	static void SetPlayingState(PlayState playState);

	static void SetPlayingRate(float value);

	static void AddToList(PlayData playData);
	static void DeleteFromList(int index);
	static void RemoveFromList(int index);

	static std::vector<PlayData> GetPlayList() { return playlists; }

	static void Update();

private:
	static PlayState playState;
	static bool playing;

	static std::vector<PlayData> playlists;

	static int playingIndex;
};

