#include "MusicPlayer.h"

std::vector<PlayData> MusicPlayer::playlists = {};
int MusicPlayer::playingIndex = 0;
bool MusicPlayer::playing = false;
PlayState MusicPlayer::playState = PlayState::SIMPLE;

void MusicPlayer::PlayInList(PlayState playState, int index, bool playAtStart)
{
    MusicPlayer::playState = playState;
    if (playlists.size() <= index)
        index = (int)playlists.size() - 1;

    PlaySoundMem(playlists[playingIndex].handle, DX_PLAYTYPE_BACK, playAtStart);
    playing = true;
}

void MusicPlayer::StopInList()
{
    StopSoundMem(playlists[playingIndex].handle);
    playing = false;
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

    if (playingIndex == index) StopInList();

    playlists.erase(playlists.begin() + index);
}

void MusicPlayer::Update()
{
    if (!playing) return;

    if (!CheckSoundMem(playlists[playingIndex].handle)) {
        StopSoundMem(playlists[playingIndex].handle);
        std::random_device rnd;
        switch (playState)
        {
        case PlayState::SIMPLE:
            playing = false;
            break;
        case PlayState::ONE_LOOP:
            PlaySoundMem(playlists[playingIndex].handle, DX_PLAYTYPE_BACK, true);
            break;
        case PlayState::ALL_LOOP:
            playingIndex++;
            if (playingIndex >= playlists.size()) playingIndex = 0;
            PlaySoundMem(playlists[playingIndex].handle, DX_PLAYTYPE_BACK, true);
            break;
        case PlayState::RANDOM:
            playingIndex = rnd() % playlists.size();
            PlaySoundMem(playlists[playingIndex].handle, DX_PLAYTYPE_BACK, true);
            break;
        default:
            break;
        }
    }
}
