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
	}

	void Bus::Start()
	{
	}

	void Bus::Update()
	{
		GameObject::Update();
		Shake();
		if (isBusActive)
		{
			BusEvent();
		}
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
		Vec3 mPos = this->GetTransform()->GetPosition();
		Vec3 mAddPos;
		Vec3 mFixedPos;
		//타이머로 해야겠군
		timer += DELTA_TIME;

		if (shake == 1)
		{
			mAddPos = Vec3(0.5f, 0.0f, -0.5f);
			mFixedPos = mPos + mAddPos * DELTA_TIME;
			if (timer >= 0.02f)
			{
				shake = 2;
				timer = 0;
			}
		}
		if (shake == 2)
		{
			mAddPos = Vec3(-0.5f, 0.0f, 0.5f);
			mFixedPos = mPos + mAddPos * DELTA_TIME;
			if (timer >= 0.02f)
			{
				shake = 1;
				timer = 0;
			}
		}
		this->GetTransform()->SetPosition(mFixedPos);
	}

	void Bus::BusEvent()
	{
		if (sequenceNum == 0)
		{
			Vec3 mPos = this->GetTransform()->GetPosition();
			Vec3 mAddPos = Vec3(-4, 0, -4);
			Vec3 mFixedPos = mPos + mAddPos * DELTA_TIME;
			mAddedDist += 1 * DELTA_TIME;
			this->GetTransform()->SetPosition(mFixedPos);
			if (mAddedDist > 4)
			{
				sequenceNum = 1;
			}
		}
	}
}