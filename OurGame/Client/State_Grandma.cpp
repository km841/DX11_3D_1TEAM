#include "pch.h"
#include "State_Grandma.h"

State_Grandma::State_Grandma(GrandmaState _meGrandmaState)
	:meGrandmaState(GrandmaState::IdleState)
{
	mTimerObj_Gm.push_back(TimerObject());
	
}

void State_Grandma::Update()
{
}

void State_Grandma::Enter()
{
}

void State_Grandma::Exit()
{
}

void State_Grandma::PlayAnimation()
{
}
