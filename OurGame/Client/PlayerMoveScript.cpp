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
	Transform* tr = GetTransform();
	RigidBody* rb = GetRigidBody();
	MeshRenderer* mr = GetMeshRenderer();

	if (IS_PRESS(KeyType::H))
	{
		tr->SetPosition(Vec3(0.0f, 0.0f, 0.f));
	}

	if (IS_PRESS(KeyType::UP))
	{
		GetRigidBody()->SetVelocity(AXIS_Z, mMoveSpeed);
	}

	if (IS_PRESS(KeyType::DOWN))
	{
		GetRigidBody()->SetVelocity(AXIS_Z, -mMoveSpeed);
	}

	if (IS_PRESS(KeyType::LEFT))
	{
		GetRigidBody()->SetVelocity(AXIS_X, -mMoveSpeed);
	}

	if (IS_PRESS(KeyType::RIGHT))
	{
		GetRigidBody()->SetVelocity(AXIS_X, mMoveSpeed);
	}

	if (IS_DOWN(KeyType::SPACE))
	{
		GetRigidBody()->SetVelocity(AXIS_Y, mMoveSpeed * 5.f);
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
