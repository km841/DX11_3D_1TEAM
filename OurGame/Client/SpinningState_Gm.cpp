#include "pch.h"
#include "SpinningState_Gm.h"
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
#include "TimerObject.h"

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
SpinningState_Gm::SpinningState_Gm()
	: State_Grandma(GrandmaState::SpinningState)
	, mCount_Ani(0) //애니메이션 카운트
{
	mTimerObj[0].SetEndTime(3.f);
	mTimerObj.push_back(TimerObject()); //1
}

void SpinningState_Gm::Initialize()
{
}

void SpinningState_Gm::Update()
{
	Grandma* pGrandma = Grandma::GetGrandma();
	Animator* pAni_Gm = pGrandma->GetAnimator();

	Transform* Tr = pGrandma->GetTransform();
	//Transform* pPlayer_Tr = PLAYER->GetTransform(); //플레이어 가져오기

	/*mTimerObj[0].Update();
	
	if(mTimerObj[0].IsFinished() == true)
		pGrandma->StateChange_Grandma(GrandmaState::SpinEndState);*/

	if (mCount_Ani > 2) {
		mCount_Ani = 0;
		pGrandma->StateChange_Grandma(GrandmaState::SpinEndState);
	}

	if (pAni_Gm->GetFrameRatio() > 0.16) {
		PlayAnimation();
		mCount_Ani++;
	}

	

}

void SpinningState_Gm::Enter()
{
	mTimerObj[0].Start();
	PlayAnimation();
}

void SpinningState_Gm::Exit()
{
	mTimerObj[0].Stop();
}

void SpinningState_Gm::PlayAnimation()
{
	Grandma* pGrandma = Grandma::GetGrandma();
	Animator* pAni_Gm = pGrandma->GetAnimator();

	pAni_Gm->Play(10, false);

}
