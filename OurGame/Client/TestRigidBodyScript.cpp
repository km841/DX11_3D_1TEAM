#include "pch.h"
#include "TestRigidBodyScript.h"
#include "GameObject.h"
#include "Input.h"
#include "RigidBody.h"
#include "Player.h"

namespace hm
{
	TestRigidBodyScript::TestRigidBodyScript()
	{
	}

	Component* TestRigidBodyScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new TestRigidBodyScript);
	}

	void TestRigidBodyScript::FixedUpdate()
	{
		RigidBody* rb = GetRigidBody();

		if (IS_DOWN(KeyType::P)) //Å×½ºÆ® À§Ä¡ ¹Ù²ã³ð
		{
			GetGameObject()->GetTransform()->SetPosition(Vec3(5.f, 0.f, 0.f));
			GetGameObject()->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			rb->SetVelocity(Vec3::Zero);
			rb->GetDynamicActor()->setAngularVelocity(Vec3::Zero);

			Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
			Vec3 myPos = GetGameObject()->GetTransform()->GetPosition();
			Vec3 dir = playerPos - myPos;
			dir.Normalize();
			dir.y = 0.5f;

			float distance = Vec3::Distance(playerPos, myPos);

			//rb->AddForce(Vec3(1.f, 1.f, 0.f));
			//rb->AddTorque(Vec3(1.f, 1.f, 0.f));
			rb->AddForceAndTorque(dir * 5);
		}
	}
}
