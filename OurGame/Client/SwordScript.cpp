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

/* Event */
#include "SceneChangeEvent.h"

SwordScript::SwordScript()
{
}

void SwordScript::Initialize()
{
	GameObject* pObj = GetGameObject();

	gpEngine->GetTool()->UseGizmo();
	//gpEngine->GetTool()->SetGameObject(pObj);
}

void SwordScript::FixedUpdate()
{
	Player* pPlayer = Player::GetPlayer();
	Transform* pPlyer_Tr = pPlayer->GetTransform();
	Transform* pTr = GetTransform();
	GameObject* pObj = GetGameObject(); // 검 오브젝트
	DirectionEvasion eDir = pPlayer->GetDirectioninfo(); // 8방향 상태 가져오는거
	
	Vec3 Pos = pPlyer_Tr->GetPosition();
	Vec3 Rot = pTr->GetRotation();

	if (eDir == DirectionEvasion::BACKWARD) {
		Pos.z += 0.25f;
		Pos.y += 0.15f;
		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(330.f, 100.f, 60.f));

	}
	if (eDir == DirectionEvasion::FORWARD) {
		Pos.z -= 0.25f;
		Pos.y += 0.15f;

		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(330.f, 270.f, 60.f));
	}
	if (eDir == DirectionEvasion::LEFT) {
		Pos.x += 0.25f;
		Pos.z += 0.f;
		Pos.y += 0.15f;
		
		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(330.f, 200.f, 60.f));
	}
	if (eDir == DirectionEvasion::RIGHT) {
		Pos.x -= 0.25f;
		Pos.z += 0.f;
		Pos.y += 0.15f;

		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(330.f, 350.f, 60.f));
	}

	if (eDir == DirectionEvasion::TOPLEFT) {
		//Pos.z += 0.125f;
		//Pos.x += 0.125f;
		Pos.y += 0.15f;

		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(330.f, 235.f, 60.f));
	}

	
	//Fsm 가져오고
	//검 콜라이더 켜기 끄지 fsm 만들고
	//8방향에 알맞는 Tr설정
	//어택했을때 알맞는 8방향 Tr 설정
	//





	pObj->GetRigidBody()->SetGeometrySize(Vec3(1.f, 0.2f, 0.2f)); //이미 만들어진 콜라이더 사이즈 변경

	pObj->GetRigidBody()->SetSimulationShapeFlag(false); // 콜라이더 끄기
	//pObj->GetRigidBody()->SetSimulationShapeFlag(true); // 콜라이더 켜기
	


	

}

Component* SwordScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new SwordScript);

}
