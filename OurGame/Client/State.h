#pragma once
#include "Player.h"
#include "TimerObject.h"

class State
{
public:
	
public:
	State(PlayerState _mePlayerState);
	virtual ~State() = default;
	
	virtual void Initialize() {}
	virtual void Update() = 0;

	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void PlayAnimation() = 0;

private:
	PlayerState mePlayerState;
	DirectionEvasion meDirectionEvasion; // 바라보는 방향 설정

protected:
	std::vector<TimerObject> mTimerObj;
};

