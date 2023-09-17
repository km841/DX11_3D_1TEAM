#include "pch.h"
#include "Bus.h"
#include <random>
#include "Transform.h"
#include "Timer.h"

namespace yj
{

	Bus::Bus()
		: GameObject(LayerType::Ground),
		shake(1)
	{
	}

	Bus::~Bus()
	{
	}
	void Bus::Initialize()
	{
		GameObject::Initialize();
		
	/*	mOriginPos = this->GetTransform()->GetPosition();
		this->GetTransform()->SetScale(Vec3(50.0f, 50.0f, 50.0f));*/

	}

	void Bus::Start()
	{
	}

	void Bus::Update()
	{
		GameObject::Update();

		if (sequence == Stanby)
		{

		}

		Shake();
	}

	void Bus::FixedUpdate()
	{
		GameObject::FinalUpdate();
	}

	void Bus::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}

	void Bus::Render()
	{
		GameObject::Render();
	}

	void Bus::Destroy()
	{
		GameObject::Destroy();
	}
	void Bus::Shake()
	{
		this->GetTransform()->SetPosition(Vec3(-17.0f, -8.0f, 33.0f));
		Vec3 mPos = this->GetTransform()->GetPosition();
		Vec3 mAddPos;
		Vec3 mFixedPos;

		if (shake == 1)
		{
			mAddPos = Vec3(5.0f, 0.0f, 0.0f);
			if (mPos.x >= mOriginPos.x + 5.0f)
			{
				shake = 2;
			}
		}
		if (shake == 2)
		{
			mAddPos = Vec3(5.0f, 0.0f, 0.0f);
			if (mPos.x >= mOriginPos.x + 5.0f)
			{
				shake = 1;
			}
		}
		mFixedPos = mPos + mAddPos * DELTA_TIME;
		this->GetTransform()->SetPosition(mFixedPos);
	}
}