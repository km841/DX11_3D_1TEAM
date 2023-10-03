#include "pch.h"
#include "BreakablePot.h"

/* Manager */
#include "Input.h"

/* Component */
#include "RigidBody.h"

namespace jh
{
	BreakablePot::BreakablePot(GameObject* _pBase, std::vector<BreakablePotCell*> _vpCells) :
		GameObject(LayerType::DecoObject),
		mbIsRestroing(false)
	{
		mpBasePot = _pBase;
		mpPotCells = _vpCells;
		mTimer.SetEndTime(3.f);

		for (int i = 0; i < mpPotCells.size(); i++)
		{
			mpPotCells[i]->GetRigidBody()->GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, true);
			mpPotCells[i]->Disable();
		}

		this->SetName(L"BreakablePot");
	}

	BreakablePot::~BreakablePot()
	{
	}

	void BreakablePot::Initialize()
	{
		for (int i = 0; i < mpPotCells.size(); i++)
		{
			mpPotCells[i]->SetOriginPos(this->GetTransform()->GetPosition() + mpPotCells[i]->GetRelativePos());
		}

		GameObject::Initialize();
	}

	void BreakablePot::Update()
	{
		GameObject::Update();

		if (IS_DOWN(KeyType::B))
		{
			BreakPots();
		}
		if (IS_DOWN(KeyType::N))
		{
			mbIsRestroing = true;
		}

		if (true == mbIsRestroing)
		{
			RestorePots();
		}
	}

	void BreakablePot::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void BreakablePot::Render()
	{
		GameObject::Render();
	}

	void BreakablePot::BreakPots()
	{
		if (true == mbIsRestroing)
			return;

		mpBasePot->Disable();

		for (int i = 0; i < mpPotCells.size(); i++)
		{
			mpPotCells[i]->Enable();
			mpPotCells[i]->GetRigidBody()->GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, false);
		}
	}

	void BreakablePot::RestorePots()
	{
		if (false == mTimer.GetIsRun())
			mTimer.Start();

		mTimer.Update();
		float progress = mTimer.GetProgress();

		for (int i = 0; i < mpPotCells.size(); i++)
		{
			mpPotCells[i]->GetRigidBody()->GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, true);
			Vec3 pos = Lerp(mpPotCells[i]->GetTransform()->GetPosition(), mpPotCells[i]->GetOriginPos(), progress);
			mpPotCells[i]->GetTransform()->SetPosition(pos);
			Vec3 rot = Lerp(mpPotCells[i]->GetTransform()->GetRotation(), Vec3(-90.f, 0.f, 90.f), progress);
			mpPotCells[i]->GetTransform()->SetRotation(rot);
			//mpPotCells[i]->Disable();
		}

		if (true == mTimer.IsFinished())
		{
			mTimer.Stop();
			mbIsRestroing = false;
		}

		//mpBasePot->Enable();
	}
}