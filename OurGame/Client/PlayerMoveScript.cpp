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
		//tr->SetPosition(Vec3::Zero);
		tr->SetPosition(Vec3(0.f, 5.f, 0.f));
	}

	//CheckPenetration(rb, LayerType::DecoObject);
	CheckPenetration(rb, LayerType::WallObject);
	//CheckPenetration(rb, LayerType::Obstacle);
	CheckPenetration(rb, LayerType::Ground);
	CheckPenetration(rb, LayerType::Monster);

	//AutoStepping(1.f);

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
		if (false == gameObjects[i]->IsEnable())
			continue;

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
			case hm::GeometryType::Mesh:
				isPenetrating = PxGeometryQuery::computePenetration(dir, depth, playerGeom, pxTr, otherGeom->triangleGeom, pxTr2);
				break;
			}
			
			if (true == isPenetrating && depth > 0.1f)
			{
				Vec3 offset = dir * (depth - 0.05f);
				Vec3 fixedPos = PLAYER->GetTransform()->GetPosition();
				PLAYER->GetTransform()->SetPosition(fixedPos + offset);
			}
		}
	}
}

void PlayerMoveScript::AutoStepping(float _height)
{
	Vec3 scale = GetRigidBody()->GetGeometrySize();
	Vec3 pos = GetTransform()->GetPosition();
	Vec3 footPos = pos;
	footPos.y -= scale.y / 2.f;

	DirectionEvasion eDir = PLAYER->GetDirectioninfo();
	Vec3 lookDir = ConvertDir(eDir);

	const auto& gameObjects = GET_SINGLE(SceneManager)->GetActiveScene()->GetGameObjects(LayerType::Ground);
	Vec3 tempScale = lookDir * scale;
	float offset = max(max(fabs(tempScale.x), fabs(tempScale.y)), fabs(tempScale.z));

	for (int i = 0; i < gameObjects.size(); ++i)
	{
		if (nullptr != gameObjects[i]->GetCollider())
		{
			bool bIsBlocked = GetCollider()->Raycast(footPos, lookDir, gameObjects[i]->GetCollider(), 0.1f + offset);
			if (true == bIsBlocked)
			{
				Vec3 steppingPos = footPos;
				float tempHeight = 0.f;
				while (tempHeight <= _height)
				{
					bool bIsStepping = GetCollider()->Raycast(steppingPos, lookDir, gameObjects[i]->GetCollider(), 0.1f + offset);
					if (false == bIsStepping)
					{
						Vec3 fixedPos = pos;
						fixedPos.y += tempHeight;
						GetTransform()->SetPosition(fixedPos + lookDir * 0.1f);
						return;
					}

					tempHeight += 0.1f;
					steppingPos.y += 0.1f;
				}
			}
		}
	}
	
}
