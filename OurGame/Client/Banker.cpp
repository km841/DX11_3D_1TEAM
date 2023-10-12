#include "pch.h"
#include "Banker.h"
#include "Animator.h"

namespace hm
{
	Banker::Banker()
	{
	}
	Banker::~Banker()
	{
	}
	void Banker::Initialize()
	{
		Npc::Initialize();
	}

	void Banker::Update()
	{
		Npc::Update();

		if (nullptr != GetAnimator())
		{
			if (GetAnimator()->GetFrameRatio() > 0.35f)
			{
				GetAnimator()->Play(L"Banker_WriteLoop", true);
			}
		}
	}

	void Banker::FixedUpdate()
	{
		Npc::FixedUpdate();
	}

	void Banker::FinalUpdate()
	{
		Npc::FinalUpdate();
	}

	void Banker::Render()
	{
		Npc::Render();
	}

	void Banker::Destroy()
	{
		Npc::Destroy();
	}
}

