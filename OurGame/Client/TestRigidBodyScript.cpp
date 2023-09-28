#include "pch.h"
#include "TestRigidBodyScript.h"
#include "GameObject.h"
#include "Input.h"
#include "RigidBody.h"

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
			//rb->AddForce(Vec3(1.f, 1.f, 0.f));
			//rb->AddTorque(Vec3(1.f, 1.f, 0.f));
			rb->AddForceAndTorque(Vec3(0.f, 1.f, 0.f) * 2.f);
		}
	}
}
