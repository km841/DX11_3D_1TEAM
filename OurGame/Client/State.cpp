#include "pch.h"
#include "State.h"

State::State(PlayerState _mePlayerState)
	: mePlayerState(PlayerState::IdleState)
{
	mTimerObj.push_back(TimerObject());

}

void State::Update()
{
}

void State::Enter()
{
}

void State::Exit()
{
}

void State::PlayAnimation()
{
}
