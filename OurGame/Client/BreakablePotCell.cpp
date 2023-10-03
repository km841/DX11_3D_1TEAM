#include "pch.h"
#include "BreakablePotCell.h"

namespace jh
{
	BreakablePotCell::BreakablePotCell() :
		GameObject(LayerType::PotCell),
		mRelativePos(Vec3::Zero),
		mOriginPos(Vec3::Zero)
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
}
