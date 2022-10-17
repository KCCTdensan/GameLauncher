#include "MusicPlayer.h"

std::vector<PlayData> MusicPlayer::playlists = {};
int MusicPlayer::playingIndex = 0;
bool MusicPlayer::playing = false;
PlayState MusicPlayer::playState = PlayState::SIMPLE;

void MusicPlayer::PlayInList(PlayState playState, int index, bool playAtStart)
{
    if (playing) return;
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
    return playing ? playlists[playingIndex] : PlayData("[Ä¶‚µ‚Ä‚¢‚Ü‚¹‚ñ]", "[System]");
}

PlayData MusicPlayer::GetPlayNextData(int offset)
{
    return playingIndex + offset < (int)playlists.size() ? playlists[playingIndex + offset] : PlayData("[ƒf[ƒ^‚È‚µ]", "[System]");
}

float MusicPlayer::GetPlayingRate()
{
    return (float)GetSoundCurrentTime(playlists[playingIndex].handle) / (float)GetSoundTotalTime(playlists[playingIndex].handle);
}

void MusicPlayer::SetPlayingState(PlayState playState)
{
    MusicPlayer::playState = playState;
}

void MusicPlayer::SetPlayingRate(float value)
{
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
