#include "pch.h"
#include "ChangeStateCondition.h"
#include "Monster.h"

ChangeStateCondition::ChangeStateCondition(MonsterBasicState _eCmpState)
	: meCmpState(_eCmpState)
{
}

BehaviorResult ChangeStateCondition::Run()
{
	Monster* pMonster = GetMonster();
	if (pMonster->GetBasicState() == meCmpState)
		return BehaviorResult::Success;
	else
		return BehaviorResult::Failure;
	
}
