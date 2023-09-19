#pragma once
#include "BehaviorCondition.h"

class ChangeStateCondition :
	public BehaviorCondition
{
public:
	ChangeStateCondition(MonsterBasicState _eNextState);
	virtual ~ChangeStateCondition() { }

public:
	virtual BehaviorResult Run();

private:
	MonsterBasicState meCmpState;

};



