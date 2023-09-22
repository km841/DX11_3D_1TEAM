#include "pch.h"
#include "ChangeStateTask.h"
#include "Monster.h"

ChangeStateTask::ChangeStateTask(MonsterBasicState _eNextState)
    :meCmpState(_eNextState)
{

}

BehaviorResult ChangeStateTask::Run()
{
    Monster* pMonster = GetMonster();

    bool check = pMonster->GetHitCheck();

    if (check == false) {
        pMonster->SetBasicState(meCmpState);
    }

    return BehaviorResult::Success;
  
}
