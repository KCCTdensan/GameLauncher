#include "MusicManager.h"

MusicManager::MusicManager()
{
	isPlaying = FALSE;
	playingName = L"";

	for (int i = 0; i < MUSIC_MAX; i++)
	{
	}
}

int MusicManager::Set(wstring stg, wstring path)
{
	for (int i = 0; i < MUSIC_MAX; i++)
	{
		music[i].name = stg;
		music[i].handle = LoadSoundMem(path.c_str());

		break;
	}

	return 0;
}

int MusicManager::Delete(wstring stg)
{
	return 0;
}

int MusicManager::DeleteAll(wstring stg)
{
	return 0;
}

int MusicManager::Play(wstring stg)
{
	for (int i = 0; i < MUSIC_MAX; i++)
	{
		isPlaying = TRUE;
		playingName = music[i].name;
		PlaySoundMem(music[i].handle, DX_PLAYTYPE_BACK, music[i].startPosition);
		break;
	}

	return 0;
}

int MusicManager::Replay(wstring stg)
{
	for (int i = 0; i < MUSIC_MAX; i++)
	{
		isPlaying = TRUE;
		playingName = music[i].name;
		PlaySoundMem(music[i].handle, DX_PLAYTYPE_BACK);
		break;
	}
	return 0;
}

int MusicManager::Stop(wstring stg)
{
	for (int i = 0; i < MUSIC_MAX; i++)
	{
		StopSoundMem(music[i].handle);
		music[i].startPosition = GetSoundCurrentTime(music[i].handle);
		break;
	}
	return 0;
}

bool MusicManager::GetPlaying()
{

	return isPlaying;
}

wstring MusicManager::GetPlayingName()
{
	return playingName;
}

int MusicManager::ChangeVolume(int num)
{
	return 0;
}
