#include "pch.h"
#include "BreakablePot.h"

/* Manager */
#include "Input.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"

namespace jh
{
	BreakablePot::BreakablePot(GameObject* _pBase, std::vector<BreakablePotCell*> _vpCells) :
		GameObject(LayerType::DecoObject),
		mbIsRestoring(false),
		mbIsWaiting(false),
		mWaitTime(1.f)
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
			mpPotCells[i]->GetTransform()->SetPosition(mpPotCells[i]->GetOriginPos());
		}

		GameObject::Initialize();
	}

	void BreakablePot::Update()
	{
		GameObject::Update();

		if (true == mbIsWaiting)
		{
			for (int i = 0; i < mpPotCells.size(); i++)
			{
				mpPotCells[i]->SetCollapsePos(mpPotCells[i]->GetTransform()->GetPosition());
				mpPotCells[i]->SetCollapseRot(mpPotCells[i]->GetTransform()->GetRotation());
			}

			mTimer.SetEndTime(4.f);

			if (false == mTimer.GetIsRun())
				mTimer.Start();

			mTimer.Update();

			if (mTimer.IsFinished())
			{
				mTimer.Stop();
				mbIsRestoring = true;
				mbIsWaiting = false;
			}
		}

		if (true == mbIsRestoring)
		{
			mTimer.SetEndTime(0.5f);
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

	void BreakablePot::OnTriggerEnter(Collider* _pOther)
	{
		if (LayerType::PlayerCol == _pOther->GetGameObject()->GetLayerType())
		{
			PxSweepHit hit;
			Vec3 dir = GetTransform()->GetPosition() - _pOther->GetGameObject()->GetTransform()->GetPosition();
			dir.Normalize();
			if (GetCollider()->Sweep(-dir, 5.f, _pOther, hit))
			{
				Vec3 pos = hit.position;
				BreakPots(pos);
			}
		}
	}

	void BreakablePot::OnTriggerStay(Collider* _pOther)
	{
	}

	void BreakablePot::OnTriggerExit(Collider* _pOther)
	{
	}

	void BreakablePot::BreakPots(const Vec3 _hitPos)
	{
		if (true == mbIsRestoring || true == mbIsWaiting)
			return;

		mpBasePot->Disable();

		for (int i = 0; i < mpPotCells.size(); i++)
		{
			//mpPotCells[i]->GetRigidBody()->GetDynamicActor()->setMass(100.f);
			mpPotCells[i]->GetRigidBody()->GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, false);
			mpPotCells[i]->Enable();

			mpPotCells[i]->CalculateForce(_hitPos);
		}

		mbIsWaiting = true;
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

			Vec3 pos = Lerp(mpPotCells[i]->GetCollapsePos(), mpPotCells[i]->GetOriginPos(), progress);
			mpPotCells[i]->GetTransform()->SetPosition(pos);
			Vec3 rot = Lerp(mpPotCells[i]->GetCollapseRot(), Vec3(-90.f, 0.f, 90.f), progress);
			mpPotCells[i]->GetTransform()->SetRotation(rot);
		}

		if (true == mTimer.IsFinished())
		{
			mTimer.Stop();

			for (int i = 0; i < mpPotCells.size(); i++)
			{
				mpPotCells[i]->Disable();
			}

			mpBasePot->Enable();
			mbIsRestoring = false;
		}
	}
}