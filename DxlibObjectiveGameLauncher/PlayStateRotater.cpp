#include "PlayStateRotater.h"

PlayStateRotater::PlayStateRotater()
    : current(PlayState::SIMPLE)
{}

void PlayStateRotater::Set(PlayState playState)
{
	current = playState;
}

void PlayStateRotater::Rotate()
{
	switch (current)
	{
	case PlayState::SIMPLE:
		current = PlayState::ONE_LOOP;
		break;
	case PlayState::ONE_LOOP:
		current = PlayState::ALL_LOOP;
		break;
	case PlayState::ALL_LOOP:
		current = PlayState::RANDOM;
		break;
	case PlayState::RANDOM:
		current = PlayState::SIMPLE;
		break;
	default:
		break;
	}
}

PlayState PlayStateRotater::GetNowState()
{
	return current;
}
