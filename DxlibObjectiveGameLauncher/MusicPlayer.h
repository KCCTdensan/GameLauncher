#pragma once
#include "MusicChest.h" // 現状Deleteするため
#include <vector>
#include "PlayData.h"
#include "PlayState.h"

class MusicPlayer
{
public:
	static void PlayInList(PlayState playState);
	static void StopInList();

	static PlayData GetPlayingData();
	static float GetPlayingRate();

private:
	static std::vector<PlayData> playlists;
};

