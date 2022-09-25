#pragma once
#include "MusicChest.h" // ����Delete���邽��
#include <vector>
#include "PlayData.h"
#include "PlayState.h"

class MusicPlayer
{
public:
	static void PlayInList(PlayState playState, int index);
	static void StopInList();

	static PlayData GetPlayingData();
	static float GetPlayingRate();

	static void AddToList(PlayData playData);
	static void RemoveFromList(int index);

private:
	static std::vector<PlayData> playlists;

	static int playingIndex;
};

