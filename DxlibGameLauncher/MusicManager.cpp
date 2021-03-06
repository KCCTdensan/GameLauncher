#include "MusicManager.h"

MusicManager::MusicManager()
{
	isPlaying = FALSE;
	playingName = "";

	for (int i = 0; i < MUSIC_MAX; i++)
	{
	}
}

int MusicManager::Set(string stg, string path)
{
	for (int i = 0; i < MUSIC_MAX; i++)
	{
		if (music[i].ExistenceFlag != FALSE)continue;

		music[i].ExistenceFlag = TRUE;
		music[i].name = stg;
		music[i].handle = LoadSoundMem(path.c_str());

		break;
	}

	return 0;
}

int MusicManager::Delete(string stg)
{
	return 0;
}

int MusicManager::DeleteAll()
{
	for (int i = 0;i < MUSIC_MAX;i++)
	{
		if (music[i].ExistenceFlag != TRUE)continue;

		isPlaying = FALSE;
		DeleteSoundMem(music[i].handle);
		music[i].ExistenceFlag = FALSE;
	}

	return 0;
}

int MusicManager::Play(string stg)
{
	for (int i = 0; i < MUSIC_MAX; i++)
	{
		if (music[i].name != stg)continue;
		isPlaying = TRUE;
		doingOutput = TRUE;
		playingName = music[i].name;
		playingHandle = music[i].handle;
		PlaySoundMem(music[i].handle, DX_PLAYTYPE_BACK, FALSE);
		break;
	}

	return 0;
}

int MusicManager::Replay(string stg)
{
	for (int i = 0; i < MUSIC_MAX; i++)
	{
		if (music[i].name != stg)continue;

		isPlaying = TRUE;
		doingOutput = TRUE;
		playingName = music[i].name;
		playingHandle = music[i].handle;
		PlaySoundMem(music[i].handle, DX_PLAYTYPE_BACK);
		break;
	}
	return 0;
}

int MusicManager::Stop(string stg)
{
	for (int i = 0; i < MUSIC_MAX; i++)
	{
		if (music[i].name != stg)continue;


		StopSoundMem(music[i].handle);
		doingOutput = FALSE;
		music[i].startPosition = GetSoundCurrentTime(music[i].handle);
		SetSoundCurrentTime(music[i].startPosition, music[i].handle);
		break;
	}
	return 0;
}

bool MusicManager::GetPlaying()
{
	return isPlaying;
}

string MusicManager::GetPlayingName()
{
	return playingName;
}

int MusicManager::GetNowPosition()
{
	return GetSoundCurrentTime(playingHandle);
}

int MusicManager::GetTotalTime()
{
	return GetSoundTotalTime(playingHandle);
}

int MusicManager::GetDoingOutput()
{
	return doingOutput;
}

int MusicManager::ChangeVolume(int num)
{
	return 0;
}
