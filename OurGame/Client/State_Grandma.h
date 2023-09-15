#pragma once
#include "Grandma.h"	
#include "TimerObject.h"
class Player;
class State_Grandma
{
public:
	State_Grandma(GrandmaState _meGrandmaState);
	virtual ~State_Grandma() = default;

	virtual void Initialize() {}
	virtual void Update() = 0;

	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void PlayAnimation() = 0;

private:
	GrandmaState meGrandmaState;
protected:
	std::vector<TimerObject> mTimerObj_Gm;
	
};