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
		mbIsRestoringTemp(false),
		mbIsRestoring(false),
		mbIsWaiting(false),
		mWaitTime(4.f)
	{
		mpBasePot = _pBase;
		mpPotCells = _vpCells;
		mWaitTimer.SetEndTime(mWaitTime);

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
			if (false == mWaitTimer.GetIsRun())
				mWaitTimer.Start();

			mWaitTimer.Update();

			if (true == mWaitTimer.IsFinished())
			{
				mWaitTimer.Stop();

				for (int i = 0; i < mpPotCells.size(); i++)
				{
					mpPotCells[i]->SetCollapsePos(mpPotCells[i]->GetTransform()->GetPosition());
					mpPotCells[i]->SetCollapseRot(mpPotCells[i]->GetTransform()->GetPhysicsRotation());
				}

				mbIsRestoringTemp = true;
				mbIsWaiting = false;
			}
		}

		if (true == mbIsRestoringTemp)
		{
			RestorePots(true);
		}
		if (true == mbIsRestoring)
		{
			RestorePots(false);
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
		if (true == mbIsRestoringTemp || true == mbIsRestoring || true == mbIsWaiting)
			return;

		mpBasePot->Disable();

		for (int i = 0; i < mpPotCells.size(); i++)
		{
			mpPotCells[i]->GetRigidBody()->GetDynamicActor()->setMass(100.f);
			mpPotCells[i]->GetRigidBody()->GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, false);
			mpPotCells[i]->Enable();

			mpPotCells[i]->CalculateForce(_hitPos);
		}

		mbIsWaiting = true;
	}

	void BreakablePot::RestorePots(bool _isTemp)
	{
		float endTime = true == _isTemp ? 0.8f : 0.1f;

		mProgressTimer.SetEndTime(endTime);

		if (false == mProgressTimer.GetIsRun())
			mProgressTimer.Start();

		mProgressTimer.Update();
		float progress = mProgressTimer.GetProgress();

		for (int i = 0; i < mpPotCells.size(); i++)
		{
			mpPotCells[i]->GetRigidBody()->GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, true);

			Vec3 tempPos = GetTransform()->GetPosition() + mpPotCells[i]->GetRelativePos() * 2.f;
			tempPos.y = mpPotCells[i]->GetOriginPos().y;

			if (true == _isTemp)
			{
				Vec3 pos = Lerp(mpPotCells[i]->GetCollapsePos(), tempPos, progress);
				mpPotCells[i]->GetTransform()->SetPosition(pos);
				Vec3 rot = Lerp(mpPotCells[i]->GetCollapseRot(), Vec3(-90.f, 0.f, 90.f), progress);
				mpPotCells[i]->GetTransform()->SetRotation(rot);
			}
			else
			{
				Vec3 pos = Lerp(tempPos, mpPotCells[i]->GetOriginPos(), progress);
				mpPotCells[i]->GetTransform()->SetPosition(pos);
			}
		}

		if (true == mProgressTimer.IsFinished())
		{
			if (true == _isTemp)
			{
				mProgressTimer.Pause();

				mTempTimer.SetEndTime(0.2f);

				if (false == mTempTimer.GetIsRun())
					mTempTimer.Start();

				mTempTimer.Update();

				if (true == mTempTimer.IsFinished())
				{
					mProgressTimer.Stop();
					mTempTimer.Stop();
					mbIsRestoringTemp = false;
					mbIsRestoring = true;
				}
			}
			else
			{
				mProgressTimer.Stop();

				for (int i = 0; i < mpPotCells.size(); i++)
				{
					mpPotCells[i]->Disable();
				}

				mpBasePot->Enable();
				mbIsRestoring = false;
			}
		}
	}
}