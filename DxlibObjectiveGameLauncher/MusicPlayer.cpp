#include "MusicPlayer.h"

std::vector<PlayData> MusicPlayer::playlists = {};
int MusicPlayer::playingIndex = 0;
bool MusicPlayer::playing = false;
PlayState MusicPlayer::playState = PlayState::SIMPLE;

void MusicPlayer::PlayInList(PlayState playState, int index, bool playAtStart)
{
    if (playlists.size() == 0) return;
    if (playing) {
        StopSoundMem(playlists[playingIndex].handle);
    }
    MusicPlayer::playState = playState;
    playingIndex = index;
    if (playlists.size() <= playingIndex)
        playingIndex = (int)playlists.size() - 1;

    PlaySoundMem(playlists[playingIndex].handle, DX_PLAYTYPE_BACK, playAtStart);
    playing = true;
}

void MusicPlayer::StopInList()
{
    if (playlists.size() == 0) return;
    StopSoundMem(playlists[playingIndex].handle);
    playing = false;
}

PlayData MusicPlayer::GetPlayingData()
{
    if (playlists.size() == 0) return PlayData("[再生していません]", "[System]");
    return playing ? playlists[playingIndex] : PlayData("[再生していません]", "[System]");
}

PlayData MusicPlayer::GetPlayNextData(int offset)
{
    if (playlists.size() == 0) return PlayData("[データなし]", "[System]");
    return playingIndex + offset < (int)playlists.size() ? playlists[playingIndex + offset] : PlayData("[データなし]", "[System]");
}

float MusicPlayer::GetPlayingRate()
{
    if (playlists.size() == 0) return 0.f;
    return (float)GetSoundCurrentTime(playlists[playingIndex].handle) / (float)GetSoundTotalTime(playlists[playingIndex].handle);
}

void MusicPlayer::SetPlayingState(PlayState playState)
{
    MusicPlayer::playState = playState;
}

void MusicPlayer::SetPlayingRate(float value)
{
    if (playlists.size() == 0) return;
    SetSoundCurrentTime((long long)((float)GetSoundTotalTime(playlists[playingIndex].handle) * value), playlists[playingIndex].handle);
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
    if (playlists.size() == 0) return;
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
