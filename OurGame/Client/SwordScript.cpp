#include "pch.h"
#include "SwordScript.h"
#include "GameObject.h"
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
#include "Grandma.h"

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
#include "SwordHeavyEffect.h"
#include "PlayerSlashScript.h"
#include "OwnerFollowScript.h"
#include "AttackState.h"

/* Event */
#include "SceneChangeEvent.h"

SwordScript::SwordScript()
{
}

void SwordScript::Initialize()
{
	GameObject* pObj = GetGameObject();

	//gpEngine->GetTool()->UseMeshTool();
	//gpEngine->GetTool()->SetGameObject(pObj);
}

void SwordScript::FixedUpdate()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	
	Transform* pPlyer_Tr = pPlayer->GetTransform();
	Transform* pTr = GetTransform();
	GameObject* pObj = GetGameObject(); // 검 오브젝트
	DirectionEvasion eDir = pPlayer->GetDirectioninfo(); // 8방향 상태 가져오는거

	bool mbAttackDir = pPlayer->GetAttackDir(); //공격방향 

	
	pObj->GetRigidBody()->SetGeometrySize(Vec3(1.f, 0.2f, 0.2f)); //이미 만들어진 콜라이더 사이즈 변경
	//pObj->GetRigidBody()->SetSimulationShapeFlag(false); // 콜라이더 끄기
	//pObj->GetRigidBody()->SetSimulationShapeFlag(true); // 콜라이더 켜기



	Vec3 Pos = pPlyer_Tr->GetPosition();
	Vec3 Rot = pTr->GetRotation();

#pragma region 칼 공격 상태
	if (mPlayerStateNum == PlayerState::AttackState) {
		if (eDir == DirectionEvasion::FORWARD && mbAttackDir == true) //정면 + 오른공
		{
			Rot = Vec3(342.f, 237.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x += 0.3f;
			Pos.y += 0.1f;
			Pos.z += 0.2f;


			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);

		}
		if (eDir == DirectionEvasion::FORWARD && mbAttackDir == false) //정면 + 왼공
		{
			Rot = Vec3(342.f, 275.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x -= 0.8f;
			Pos.y += 0.1f;
			Pos.z += 0.4f;


			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);
		}

		if (eDir == DirectionEvasion::BACKWARD && mbAttackDir == true)  //뒤쪽 + 오른공
		{
			Rot = Vec3(342.f, 57.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x -= 0.3f;
			Pos.y += 0.1f;
			Pos.z -= 0.2f;

			
			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);
	
		}
		if (eDir == DirectionEvasion::BACKWARD && mbAttackDir == false) //뒤쪽 + 왼공
		{
			Rot = Vec3(342.f, 95.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x += 0.8f;
			Pos.y += 0.1f;
			Pos.z -= 0.4f;

		
			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);

		}

		if (eDir == DirectionEvasion::LEFT && mbAttackDir == true)  //왼쪽 + 오른공
		{
			Rot = Vec3(342.f, 147.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x -= 0.2f;
			Pos.y += 0.1f;
			Pos.z += 0.4f;


			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);
		}
		if (eDir == DirectionEvasion::LEFT && mbAttackDir == false) //왼쪽 + 왼공
		{
			Rot = Vec3(342.f, 185.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x -= 0.4f;
			Pos.y += 0.1f;
			Pos.z -= 0.8f;


			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);
		}

		if (eDir == DirectionEvasion::RIGHT && mbAttackDir == true)  //오른쪽 + 오른공
		{
			Rot = Vec3(342.f, 327.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x += 0.2f;
			Pos.y += 0.1f;
			Pos.z -= 0.4f;


			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);
		}
		if (eDir == DirectionEvasion::RIGHT && mbAttackDir == false) //오른쪽 + 왼공
		{
			Rot = Vec3(342.f, 365.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x += 0.4f;
			Pos.y += 0.1f;
			Pos.z += 0.8f;


			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);
		}

		if (eDir == DirectionEvasion::TOPLEFT && mbAttackDir == true) //왼쪽위 + 오른공
		{
			Rot = Vec3(342.f, 192.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x += 0.3f;
			Pos.y += 0.1f;
			Pos.z += 0.3f;


			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);

		}

		if (eDir == DirectionEvasion::TOPLEFT && mbAttackDir == false) //왼쪽위 + 왼공
		{
			Rot = Vec3(342.f, 230.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x -= 0.8f;
			Pos.y += 0.1f;
			Pos.z -= 0.4f;


			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);

		}

		if (eDir == DirectionEvasion::TOPRIGHT && mbAttackDir == true) //오른쪽위 + 오른공
		{
			Rot = Vec3(342.f, -78.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x += 0.3f;
			Pos.y += 0.1f;
			Pos.z -= 0.3f;


			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);

		}

		if (eDir == DirectionEvasion::TOPRIGHT && mbAttackDir == false) //오른쪽위 + 왼공
		{
			Rot = Vec3(342.f, -40.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x -= 0.4f;
			Pos.y += 0.1f;
			Pos.z += 0.8f;


			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);

		}

		if (eDir == DirectionEvasion::BOTTOMLEFT && mbAttackDir == true) //왼쪽아래 + 오른공
		{
			Rot = Vec3(342.f, 102.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x -= 0.3f;
			Pos.y += 0.1f;
			Pos.z += 0.3f;


			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);

		}

		if (eDir == DirectionEvasion::BOTTOMLEFT && mbAttackDir == false) //왼쪽아래 + 오른공
		{
			Rot = Vec3(342.f, 140.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x += 0.4f;
			Pos.y += 0.1f;
			Pos.z -= 0.8f;


			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);

		}

		if (eDir == DirectionEvasion::BOTTOMRIGHT && mbAttackDir == true) //오른쪽아래 + 오른공
		{
			Rot = Vec3(342.f, 12.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x -= 0.3f;
			Pos.y += 0.1f;
			Pos.z -= 0.3f;


			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);

		}

		if (eDir == DirectionEvasion::BOTTOMRIGHT && mbAttackDir == false) //오른쪽아래 + 왼공
		{
			Rot = Vec3(342.f, 50.f, 342.f);

			Pos = pPlyer_Tr->GetPosition();
			Pos.x += 0.8f;
			Pos.y += 0.1f;
			Pos.z += 0.4f;


			pTr->SetRotation(Rot);
			pTr->SetPosition(Pos);

		}
	}
		
#pragma endregion

#pragma region 칼 기본상태
	if (mPlayerStateNum != PlayerState::AttackState) {
		if (eDir == DirectionEvasion::BACKWARD) {
			Pos.z += 0.2f;
			Pos.y += 0.2f;
			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(330.f, 100.f, 60.f));

		}
		if (eDir == DirectionEvasion::FORWARD) {
			Pos.z -= 0.2f;
			Pos.y += 0.2f;

			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(330.f, 270.f, 60.f));
		}
		if (eDir == DirectionEvasion::LEFT) {
			Pos.x += 0.2f;
			Pos.z += 0.f;
			Pos.y += 0.2f;

			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(330.f, 200.f, 60.f));
		}
		if (eDir == DirectionEvasion::RIGHT) {
			Pos.x -= 0.2f;
			Pos.z += 0.f;
			Pos.y += 0.2f;

			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(330.f, 350.f, 60.f));
		}

		if (eDir == DirectionEvasion::TOPLEFT) {
			Pos.z -= 0.125f;
			Pos.x += 0.125f;
			Pos.y += 0.2f;

			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(330.f, 240.f, 60.f));
		}

		if (eDir == DirectionEvasion::TOPRIGHT) {
			//Pos.z += 0.125f;
			//Pos.x += 0.125f;
			Pos.y += 0.2f;

			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(330.f, 310.f, 60.f));
		}

		if (eDir == DirectionEvasion::BOTTOMLEFT) {
			//Pos.z += 0.125f;
			//Pos.x += 0.125f;
			Pos.y += 0.2f;

			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(330.f, 150.f, 60.f));
		}

		if (eDir == DirectionEvasion::BOTTOMRIGHT) {
			//Pos.z += 0.125f;
			//Pos.x += 0.125f;
			Pos.y += 0.2f;

			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(330.f, 50.f, 60.f));
		}
	}
#pragma endregion
	
	//Fsm 가져오고 O 
	//검 콜라이더 켜기 끄지 fsm 만들고 O
	//8방향에 알맞는 Tr설정 O
	//어택했을때 알맞는 8방향 Tr 설정 X
	//





	


	

}

void SwordScript::SetPlayerState(PlayerState _eStateNum)
{
	mPlayerStateNum = _eStateNum;

	if (PlayerState::AttackState == mPlayerStateNum)
	{
		int a = 0;
	}
}

Component* SwordScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new SwordScript);

}
