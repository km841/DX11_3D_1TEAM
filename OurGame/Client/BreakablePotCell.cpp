#include "pch.h"
#include "BreakablePotCell.h"

#include "RigidBody.h"

namespace jh
{
	BreakablePotCell::BreakablePotCell() :
		GameObject(LayerType::PotCell),
		mRelativePos(Vec3::Zero),
		mOriginPos(Vec3::Zero),
		mCollapsePos(Vec3::Zero)
	{
		this->SetName(L"PotCell");
	}

	BreakablePotCell::~BreakablePotCell()
	{
	}

	void BreakablePotCell::Initialize()
	{
		GameObject::Initialize();
	}

	void BreakablePotCell::Update()
	{
		GameObject::Update();
	}

	void BreakablePotCell::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void BreakablePotCell::Render()
	{
		GameObject::Render();
	}

	void BreakablePotCell::CalculateForce(const Vec3 _hitPos)
	{
		Vec3 force = _hitPos - GetTransform()->GetPosition();
		float distance = force.Length();
		force.y = 0.f;

		if (distance < 1.f)
		{
			GetRigidBody()->AddForce((force) * -5);
		}
		else if (1.f <= distance && distance < 2.f)
		{
			GetRigidBody()->AddForce((force) * -2.5);
		}
		else
		{
			GetRigidBody()->AddForce((force) * -1);
		}
	}
}
