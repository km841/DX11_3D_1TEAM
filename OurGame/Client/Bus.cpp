#include "pch.h"
#include "Bus.h"
#include <random>
#include "Transform.h"
#include "Timer.h"
#include "EventSystem.h"
#include "TextBox.h"
#include "Player.h"

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

	}

	void Bus::BusEvent()
	{
		if (sequenceNum == 0)
		{
			Vec3 mPos = this->GetTransform()->GetPosition();
			Vec3 mAddPos = Vec3(-4, 0, -4);
			Vec3 mFixedPos = mPos + mAddPos * DELTA_TIME * 2;
			mAddedDist += 1 * DELTA_TIME;
			this->GetTransform()->SetPosition(mFixedPos);
			if (mAddedDist > 2)
			{
				sequenceNum = 1;
				TEXTBOX->SetWriteTexts(0, 2,"BusArriveEvent");
				TEXTBOX->Apear();
			}
		}
		if (EVENTSYSTEM->CheckEventOn("BusArriveEvent"))
		{
			sequenceNum = 2;
		}
		if (sequenceNum == 2)
		{
			mbIsArrived = true;
			Vec3 mPos = this->GetTransform()->GetPosition();
			Vec3 mAddPos = Vec3(-4, 0, -4);
			Vec3 mFixedPos = mPos + mAddPos * DELTA_TIME * 2;
			mAddedDist += 1 * DELTA_TIME;
			if(mAddedDist > 3 && mAddedDist <= 10)
				this->GetTransform()->SetPosition(mFixedPos);
			if (mAddedDist > 10)
			{
				sequenceNum = 3;
			}
		}
	}
}