#include "pch.h"
#include "CameraHolder.h"

namespace hm
{
	CameraHolder::CameraHolder()
		: GameObject(LayerType::Unknown)
	{
	}

	CameraHolder::~CameraHolder()
	{
	}

	void CameraHolder::Initialize()
	{
		GameObject::Initialize();
	}

	void CameraHolder::Update()
	{
		GameObject::Update();
	}

	void CameraHolder::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void CameraHolder::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}

	void CameraHolder::Render()
	{
		GameObject::Render();
	}

	void CameraHolder::Destroy()
	{
		GameObject::Destroy();
	}
}


