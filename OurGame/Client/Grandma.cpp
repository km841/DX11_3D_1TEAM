#include "pch.h"
#include "Grandma.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Animator.h"

/*State_Grandma 모음*/
#include "State_Grandma.h"
#include "IdleState_Gm.h"

 Grandma* Grandma::spGrandma;

Grandma::Grandma()
    : GameObject(LayerType::Grandma_Boss)
    , mActiveState_Grandma(NULL)
{
    AssertEx(spGrandma == nullptr, L"이미 정적 Grandma 존재함");
    spGrandma = this; //정적변수 선언

    /*↓↓↓계속 추가해줘야됨 State Class 추가 할때 마다*/
    mState_Grandma[int(GrandmaState::IdleState)] = new IdleState_Gm;

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
