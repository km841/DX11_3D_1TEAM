#include "pch.h"
#include "EtranceHallDoor.h"

#include "Transform.h"

#include "Input.h"

namespace yj
{

	EtranceHallDoor::EtranceHallDoor(GameObject* _leftDoor, GameObject* _rightDoor)
		:GameObject(LayerType::Obstacle)
	{
	}

	EtranceHallDoor::~EtranceHallDoor()
	{
	}

	void EtranceHallDoor::Update()
	{
		if (IS_DOWN(KeyType::H))
		{

		}
		if (isOpen)
		{
			Open();
		}
	}

	void EtranceHallDoor::Open()
	{

		Vec3 mLPos = mLeftDoor->GetTransform()->GetPosition();
		
		mLeftDoor->GetTransform()->SetPosition(Vec3());

		Vec3 mRPos = mRightDoor->GetTransform()->GetPosition();
		mRightDoor->GetTransform()->SetPosition(Vec3());
	}
}