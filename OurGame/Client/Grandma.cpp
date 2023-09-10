#include "pch.h"
#include "Grandma.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Animator.h"

/*State_Grandma 모음*/
#include "State_Grandma.h"
#include "IdleState_Gm.h"
#include "RangeAttack01State_Gm.h"
#include "Teleport_InState_Gm.h"
#include "RangeAttack02State_Gm.h"
#include "AngryMotionState_Gm.h"
#include "SpinStartState_Gm.h"
#include "SpinningState_Gm.h"
#include "SpinEndState_Gm.h"
#include "DeathState_Gm.h"
#include "Teleport_OutState_Gm.h"
#include "SmallTransStartState_Gm.h"
#include "SmallTransEndState_Gm.h"
#include "BigTransStartState_Gm.h"
#include "SmallAttack01State_Gm.h"
#include "Small_IdleState_Gm.h"
#include "BigTransEndState_Gm.h"

 Grandma* Grandma::spGrandma;

Grandma::Grandma()
    : GameObject(LayerType::Grandma_Boss)
    , mActiveState_Grandma(NULL)
{
    AssertEx(spGrandma == nullptr, L"이미 정적 Grandma 존재함");
    spGrandma = this; //정적변수 선언

    /*↓↓↓계속 추가해줘야됨 State Class 추가 할때 마다*/
    mState_Grandma[int(GrandmaState::IdleState)] = new IdleState_Gm;
    mState_Grandma[int(GrandmaState::RangeAttack01State)] = new RangeAttack01State_Gm;
    mState_Grandma[int(GrandmaState::Teleport_InState)] = new Teleport_InState_Gm;
    mState_Grandma[int(GrandmaState::RangeAttack02State)] = new RangeAttack02State_Gm;
    mState_Grandma[int(GrandmaState::AngryMotionState)] = new AngryMotionState_Gm;
    mState_Grandma[int(GrandmaState::SpinStartState)] = new SpinStartState_Gm;
    mState_Grandma[int(GrandmaState::SpinningState)] = new SpinningState_Gm;
    mState_Grandma[int(GrandmaState::SpinEndState)] = new SpinEndState_Gm;
    mState_Grandma[int(GrandmaState::DeathState)] = new DeathState_Gm;
    mState_Grandma[int(GrandmaState::Teleport_OutState)] = new Teleport_OutState_Gm;
    mState_Grandma[int(GrandmaState::SmallTransStartState)] = new SmallTransStartState_Gm;
    mState_Grandma[int(GrandmaState::SmallTransEndState)] = new SmallTransEndState_Gm;
    mState_Grandma[int(GrandmaState::BigTransStartState)] = new BigTransStartState_Gm;
    mState_Grandma[int(GrandmaState::SmallAttack01State)] = new SmallAttack01State_Gm;
    mState_Grandma[int(GrandmaState::Small_IdleState)] = new Small_IdleState_Gm;
    mState_Grandma[int(GrandmaState::BigTransEndState)] = new BigTransEndState_Gm;

}

Grandma::~Grandma()
{
    for (size_t i = 0; i < GRANDMA_STATE_COUNT; i++)
    {
        SAFE_DELETE(mState_Grandma[i]);
    }
}

void Grandma::Initialize()
{
    GameObject::Initialize();

    StateChange_Grandma(GrandmaState::IdleState);

#pragma region "애니메이션 이름 변경"
    /*애니메이션 이름 변경*/
    GetAnimator()->RenameAnimation(0, L"Grandma_Idle"); //이름변경
    GetAnimator()->SetLoop(0, true); //루프
    GetAnimator()->SetHasExitFlag(0, true); // 기존 애니메이션 다끝나고 실행 f ? t

    GetAnimator()->RenameAnimation(1, L"RangeAttack01");
    GetAnimator()->SetLoop(1, true);
    GetAnimator()->SetHasExitFlag(1, true);

    GetAnimator()->RenameAnimation(6, L"Teleport_In"); 
    GetAnimator()->SetLoop(6, true); 
    GetAnimator()->SetHasExitFlag(6, true);

    GetAnimator()->RenameAnimation(7, L"RangeAttack02");
    GetAnimator()->SetLoop(7, true);
    GetAnimator()->SetHasExitFlag(7, true);

    GetAnimator()->RenameAnimation(8, L"AngryMotion");
    GetAnimator()->SetLoop(8, true);
    GetAnimator()->SetHasExitFlag(8, true);

    GetAnimator()->RenameAnimation(9, L"SpinStart");
    GetAnimator()->SetLoop(9, true);
    GetAnimator()->SetHasExitFlag(9, true);

    GetAnimator()->RenameAnimation(10, L"Spinning");
    GetAnimator()->SetLoop(10, true);
    GetAnimator()->SetHasExitFlag(10, true);

    GetAnimator()->RenameAnimation(11, L"SpinEnd");
    GetAnimator()->SetLoop(11, true);
    GetAnimator()->SetHasExitFlag(11, true);

    GetAnimator()->RenameAnimation(12, L"Death");
    GetAnimator()->SetLoop(12, true);
    GetAnimator()->SetHasExitFlag(12, true);

    GetAnimator()->RenameAnimation(13, L"Teleport_Out");
    GetAnimator()->SetLoop(13, true);
    GetAnimator()->SetHasExitFlag(13, true);

    GetAnimator()->RenameAnimation(14, L"SmallTransStart");
    GetAnimator()->SetLoop(14, true);
    GetAnimator()->SetHasExitFlag(14, true);

    GetAnimator()->RenameAnimation(16, L"SmallTransEnd");
    GetAnimator()->SetLoop(16, true);
    GetAnimator()->SetHasExitFlag(16, true);

    GetAnimator()->RenameAnimation(17, L"BigTransStart");
    GetAnimator()->SetLoop(17, true);
    GetAnimator()->SetHasExitFlag(17, true);

    GetAnimator()->RenameAnimation(18, L"SmallAttack01");
    GetAnimator()->SetLoop(18, true);
    GetAnimator()->SetHasExitFlag(18, true);

    GetAnimator()->RenameAnimation(19, L"Small_Idle");
    GetAnimator()->SetLoop(19, true);
    GetAnimator()->SetHasExitFlag(19, true);

    GetAnimator()->RenameAnimation(24, L"BigTransEnd");
    GetAnimator()->SetLoop(24, true);
    GetAnimator()->SetHasExitFlag(24, true);
#pragma endregion


#pragma region "쓰지않는 ani 모음"

    GetAnimator()->RenameAnimation(2, L"NULL");
    GetAnimator()->SetLoop(2, true);
    GetAnimator()->SetHasExitFlag(2, true);

    GetAnimator()->RenameAnimation(3, L"NULL");
    GetAnimator()->SetLoop(3, true);
    GetAnimator()->SetHasExitFlag(3, true);

    GetAnimator()->RenameAnimation(4, L"NULL");
    GetAnimator()->SetLoop(4, true);
    GetAnimator()->SetHasExitFlag(4, true);

    GetAnimator()->RenameAnimation(15, L"NULL");
    GetAnimator()->SetLoop(15, true);
    GetAnimator()->SetHasExitFlag(15, true);

    GetAnimator()->RenameAnimation(20, L"NULL");
    GetAnimator()->SetLoop(20, true);
    GetAnimator()->SetHasExitFlag(20, true);

    GetAnimator()->RenameAnimation(21, L"NULL");
    GetAnimator()->SetLoop(21, true);
    GetAnimator()->SetHasExitFlag(21, true);

    GetAnimator()->RenameAnimation(22, L"NULL");
    GetAnimator()->SetLoop(22, true);
    GetAnimator()->SetHasExitFlag(22, true);

    GetAnimator()->RenameAnimation(23, L"NULL");
    GetAnimator()->SetLoop(23, true);
    GetAnimator()->SetHasExitFlag(23, true);

    GetAnimator()->RenameAnimation(5, L"Error"); 
    GetAnimator()->SetLoop(5,true); 
    GetAnimator()->SetHasExitFlag(5, true); 

    GetAnimator()->RenameAnimation(25, L"Error_FIx");
    GetAnimator()->SetLoop(25, true);
    GetAnimator()->SetHasExitFlag(25, true);

#pragma endregion

   
}

void Grandma::Update()
{
    GameObject::Update();
    mActiveState_Grandma->Update();
}

void Grandma::FixedUpdate()
{
    GameObject::FixedUpdate();
}

void Grandma::FinalUpdate()
{
    GameObject::FinalUpdate();
}

void Grandma::Render()
{
    GameObject::Render();
}

void Grandma::Destroy()
{
    GameObject::Destroy();
}

void Grandma::OnTriggerEnter(Collider* pOtherCollider)
{
}

void Grandma::OnTriggerStay(Collider* pOtherCollider)
{
}

void Grandma::OnTriggerExit(Collider* pOtherCollider)
{
}

void Grandma::StateChange_Grandma(GrandmaState _eState)
{
    if (mActiveState_Grandma != nullptr) {
        mActiveState_Grandma->Exit();
    }

    mActiveState_Grandma = mState_Grandma[int(_eState)];
    mActiveState_Grandma->Enter();
}

Grandma* Grandma::GetGrandma()
{
    AssertEx(spGrandma != nullptr, L"Grandma가 Nullptr 이다 _ GetGrandma()~");
    return spGrandma;
}
