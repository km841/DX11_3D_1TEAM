#include "pch.h"
#include "Elevator.h"
#include "Input.h"
#include "Rigidbody.h"
#include "Collider.h"
namespace yj
{

	void Elevator::Initialize()
	{
	}

	void Elevator::Start()
	{
	}

	void Elevator::Update()
	{
		if (IS_UP(KeyType::A))
		{
			BarricadeOn();
		}
		if (IS_UP(KeyType::S))
		{
			BarricadeOff();
		}

		GameObject* A;
		if(A->GetRigidBody()->GetCollider()->IsCollision();

	}

	void Elevator::FixedUpdate()
	{
	}

	void Elevator::FinalUpdate()
	{
	}
}