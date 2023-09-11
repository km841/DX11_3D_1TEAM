#include "pch.h"
#include "PlayerMoveScript.h"
#include "GameObject.h"
#include "Input.h"
#include "Transform.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Collider.h"
#include "SceneManager.h"

PlayerMoveScript::PlayerMoveScript()
	: mMoveSpeed(2.f)
{
}

void PlayerMoveScript::FixedUpdate()
{
	GameObject* obj = GetGameObject(); // == Getowner();
	Transform* tr = GetTransform();
	RigidBody* rb = GetRigidBody();
	MeshRenderer* mr = GetMeshRenderer();

	if (IS_PRESS(KeyType::H))
	{
		tr->SetPosition(Vec3(0.0f, 0.0f, 0.f));
	}

	if (IS_PRESS(KeyType::UP))
	{
		rb->SetVelocity(AXIS_Z, mMoveSpeed);
	}

	if (IS_PRESS(KeyType::DOWN))
	{
		rb->SetVelocity(AXIS_Z, -mMoveSpeed);
	}

	if (IS_PRESS(KeyType::LEFT))
	{
		rb->SetVelocity(AXIS_X, -mMoveSpeed);
	}

	if (IS_PRESS(KeyType::RIGHT))
	{
		rb->SetVelocity(AXIS_X, mMoveSpeed);
	}

	if (IS_DOWN(KeyType::SPACE))
	{
		rb->SetVelocity(AXIS_Y, mMoveSpeed * 5.f);
	}

	const auto& gameObjects = GET_SINGLE(SceneManager)->GetActiveScene()->GetGameObjects(LayerType::WallObject);
	
	for (int i = 0; i < gameObjects.size(); ++i)
	{
		if (gameObjects[i]->GetCollider())
		{
			PxVec3 dir;
			float depth;
			PxBoxGeometry geom0 = rb->GetGeometries()->boxGeom;
			PxTransform pxTr(tr->GetPosition());
			PxBoxGeometry geom1 = gameObjects[i]->GetRigidBody()->GetGeometries()->boxGeom;
			PxTransform pxTr2(gameObjects[i]->GetTransform()->GetPosition());

			bool isPenetrating = PxGeometryQuery::computePenetration(dir, depth, geom0, pxTr, geom1, pxTr2);
			if (true == isPenetrating)
			{
				rb->SetVelocity(dir);
			}
		}
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
