#include "MusicPlayer.h"

std::vector<PlayData> MusicPlayer::playlists = {};
int MusicPlayer::playingIndex = 0;

void MusicPlayer::PlayInList(PlayState playState, int index)
{

}

void MusicPlayer::StopInList()
{
}

PlayData MusicPlayer::GetPlayingData()
{
    return PlayData();
}

float MusicPlayer::GetPlayingRate()
{
    return 0.0f;
}

void MusicPlayer::AddToList(PlayData playData)
{
    playlists.push_back(playData);
}

void MusicPlayer::RemoveFromList(int index)
{
    if (playlists.size() <= index) return;

    playlists.erase(playlists.begin() + index);
}
