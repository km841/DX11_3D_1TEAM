#include "pch.h"
#include "PlayerMoveScript.h"
#include "GameObject.h"
#include "Input.h"
#include "Transform.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Collider.h"
#include "SceneManager.h"
#include "PaperBurnScript.h"
#include "Player.h"

PlayerMoveScript::PlayerMoveScript()
	: mMoveSpeed(NULL)
{
}

void PlayerMoveScript::FixedUpdate()
{
	Player* pPlayer = Player::GetPlayer();

	GameObject* obj = GetGameObject(); // == Getowner();
	Transform* tr = GetTransform();
	RigidBody* rb = GetRigidBody();
	MeshRenderer* mr = GetMeshRenderer();

	Vec3 mPos = tr->GetLook();

	
	if (IS_DOWN(KeyType::H))
	{
		tr->SetPosition(Vec3::Zero);
	}
	
	

	CheckPenetration(rb, LayerType::WallObject);
	CheckPenetration(rb, LayerType::Obstacle);

	PaperBurnScript* pPaperBurn = GetGameObject()->GetScript<PaperBurnScript>();
	pPaperBurn->SetReverse(true);
	pPaperBurn->SetFinishedCallback(std::bind(&PlayerMoveScript::SimpleFunc, this));
	if (IS_DOWN(KeyType::F))
	{
		pPaperBurn->SetPaperBurn();
	}

	if (pPaperBurn->IsFinished())
	{
		// 페이퍼번이 끝남
		int a = 0;
	}

	//Vec3 mPos = GetTransform()->GetPosition();
	//Vec3 mScale = GetTransform()->GetScale();
	//Vec3 mFootPos = Vec3(mPos.x, mPos.y - mScale.y / 2.f, mPos.z);
	//Vec3 mBottomDir = Vec3(0.f, -1.f, 0.f);
	//
	//const auto& gameObjects = GET_SINGLE(SceneManager)->GetActiveScene()->GetGameObjects(LayerType::Ground);
	//
	//bool bIsGround = false;
	//for (int i = 0; i < gameObjects.size(); ++i)
	//{
	//	if (gameObjects[i]->GetCollider())
	//	{
	//		if (GetCollider()->Raycast(mFootPos, mBottomDir, gameObjects[i]->GetCollider(), 1.f))
	//		{
	//			bIsGround = true;
	//		}
	//	}
	//}	

	//if (false == bIsGround)
	//{
	//	GetRigidBody()->ApplyGravity();
	//	GetRigidBody()->SetGround(false);
	//}
	//else
	//{
	//	GetRigidBody()->SetGround(true);
	//	GetRigidBody()->RemoveGravity();

	//	if (0.f < fabs(GetRigidBody()->GetVelocity().y))
	//		GetRigidBody()->SetVelocity(AXIS_Y, 0.f);
	//}
}

Component* PlayerMoveScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new PlayerMoveScript);
}

void PlayerMoveScript::CheckPenetration(RigidBody* _rigidBody, LayerType _eLayertype)
{
	const auto& gameObjects = GET_SINGLE(SceneManager)->GetActiveScene()->GetGameObjects(_eLayertype);

	for (int i = 0; i < gameObjects.size(); ++i)
	{
		if (gameObjects[i]->GetCollider())
		{
			PxVec3 dir;
			float depth;
			PxCapsuleGeometry playerGeom = _rigidBody->GetGeometries()->capsuleGeom;
			PxTransform pxTr = _rigidBody->GetPhysicsTransform();
			Geometries* otherGeom = gameObjects[i]->GetRigidBody()->GetGeometries();
			PxTransform pxTr2 = gameObjects[i]->GetRigidBody()->GetPhysicsTransform();

			bool isPenetrating = false;
			switch (gameObjects[i]->GetRigidBody()->GetGeometryType())
			{
			case hm::GeometryType::Sphere:
				isPenetrating = PxGeometryQuery::computePenetration(dir, depth, playerGeom, pxTr, otherGeom->sphereGeom, pxTr2);
				break;
			case hm::GeometryType::Box:
				isPenetrating = PxGeometryQuery::computePenetration(dir, depth, playerGeom, pxTr, otherGeom->boxGeom, pxTr2);
				break;
			case hm::GeometryType::Capsule:
				isPenetrating = PxGeometryQuery::computePenetration(dir, depth, playerGeom, pxTr, otherGeom->capsuleGeom, pxTr2);
				break;
			case hm::GeometryType::Plane:
				isPenetrating = PxGeometryQuery::computePenetration(dir, depth, playerGeom, pxTr, otherGeom->planeGeom, pxTr2);
				break;
			}
			
			if (true == isPenetrating)
			{
				_rigidBody->SetVelocity(dir);
			}
		}
	}
}
