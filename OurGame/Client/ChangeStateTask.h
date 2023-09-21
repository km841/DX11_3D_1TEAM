#pragma once
#include "BehaviorTask.h"
class ChangeStateTask :
    public BehaviorTask
{
public:
	ChangeStateTask(MonsterBasicState _eNextState);
	virtual ~ChangeStateTask() { }

public:
	virtual BehaviorResult Run();

private:
	MonsterBasicState meCmpState;
};

