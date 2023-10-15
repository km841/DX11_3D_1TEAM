#include "pch.h"
#include "PotDoor.h"
#include "PaperBurnScript.h"

namespace hm
{
	PotDoor::PotDoor()
		: GameObject(LayerType::Unknown)
	{
		mTimer.SetEndTime(2.f);
	}

	PotDoor::~PotDoor()
	{
	}

	void PotDoor::Initialize()
	{
		GameObject::Initialize();
	}

	void PotDoor::Update()
	{
		GameObject::Update();
		mTimer.Update();

		if (mTimer.IsFinished() && false == mbIsFinished)
		{
			if (nullptr != mCreatedCallback01)
				mCreatedCallback01();
			if (nullptr != mCreatedCallback02)
				mCreatedCallback02(a);
			if (nullptr != mCreatedCallback03)
				mCreatedCallback03(b);

			mbIsFinished = true;
			GetScript<PaperBurnScript>()->Reset();
			GetScript<PaperBurnScript>()->SetReverse(false);
			GetScript<PaperBurnScript>()->SetPaperBurn();
			mTimer.Stop();
		}
	}

	void PotDoor::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void PotDoor::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}

	void PotDoor::Render()
	{
		GameObject::Render();
	}

	void PotDoor::Destroy()
	{
		GameObject::Destroy();
	}

	void PotDoor::SetPaperBurn()
	{
		GetScript<PaperBurnScript>()->SetPotPaperBurn();
		GetScript<PaperBurnScript>()->SetReverse(true);
		GetScript<PaperBurnScript>()->SetSpeed(2.f);
		mTimer.Start();
	}
}

