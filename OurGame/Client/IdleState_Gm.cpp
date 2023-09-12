#include "pch.h"
#include "IdleState_Gm.h"
#include "Engine.h"

/* Resource */
#include "MeshData.h"
#include "Material.h"
#include "Mesh.h"

/* Manager */
#include "PrefabManager.h"
#include "EventManager.h"
#include "Factory.h"
#include "CollisionManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "Resources.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "WallObject.h"
#include "Npc.h"
#include "Monster.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Animator.h"

/* Script */
#include "PlayerMoveScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"

/* Event */
#include "SceneChangeEvent.h"

#include <ctime>
#include <random>

std::mt19937 mt(static_cast<unsigned int>(std::time(nullptr)));
std::uniform_int_distribution<int> stateDistribution(1, 3);

IdleState_Gm::IdleState_Gm()
	: State_Grandma(GrandmaState::IdleState)
	, mDuplicateIndex(NULL)
{
	
}

void IdleState_Gm::Initialize()
{
}

void IdleState_Gm::Update()
{
	Grandma* pGrandma = Grandma::GetGrandma();
	Animator* pAni_Gm = pGrandma->GetAnimator();

	if (pAni_Gm->GetFrameRatio() > 0.4f)
	{
		int mRandomIndex = stateDistribution(mt);// 1~3 중 랜덤으로 하나 선택
		if (mDuplicateIndex != mRandomIndex) // 중복체크 인덱스 랑 다르면 번호 저장
		{
			mDuplicateIndex = mRandomIndex;
		}
		else // 중복체크 인덱스랑 같은면 , 랜더 돌려버리기
		{
			mRandomIndex = stateDistribution(mt);
		}

		// 아래 식까지 총 랜덤 두번 걸렷는데도 똑같은 숫자면 운이지뭐..
		if(1 == mRandomIndex)
			pGrandma->StateChange_Grandma(GrandmaState::SpinStartState);
		if(2 == mRandomIndex)
			pGrandma->StateChange_Grandma(GrandmaState::RangeAttack01State);
		if(3 == mRandomIndex)
			pGrandma->StateChange_Grandma(GrandmaState::RangeAttack02State);
	}










	if (IS_DOWN(KeyType::UP))
	{
		pGrandma->StateChange_Grandma(GrandmaState::SpinStartState);
	}
	if (IS_DOWN(KeyType::RIGHT))
	{
		pGrandma->StateChange_Grandma(GrandmaState::SmallTransStartState);
	}
	if (IS_DOWN(KeyType::DOWN))
	{
		pGrandma->StateChange_Grandma(GrandmaState::RangeAttack01State);
	}
	if (IS_DOWN(KeyType::LEFT))
	{
		pGrandma->StateChange_Grandma(GrandmaState::RangeAttack02State);
	}
}

void IdleState_Gm::Enter()
{
	PlayAnimation();
}

void IdleState_Gm::Exit()
{
}

void IdleState_Gm::PlayAnimation()
{
	Grandma* pGrandma = Grandma::GetGrandma();
	Animator* pAni_Gm = pGrandma->GetAnimator();

	pAni_Gm->Play(0, false);

}
