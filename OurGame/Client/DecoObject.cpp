#include "pch.h"
#include "DecoObject.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Timer.h"

namespace hm
{
	DecoObject::DecoObject()
		: GameObject(LayerType::DecoObject)
	{
	}
	DecoObject::~DecoObject()
	{
	}
	void DecoObject::Initialize()
	{
		GameObject::Initialize();
	}
	void DecoObject::Update()
	{
		GameObject::Update();
	}

	void DecoObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void DecoObject::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}

	void DecoObject::Render()
	{
		GameObject::Render();
	}

	void DecoObject::Destroy()
	{
		GameObject::Destroy();
	}
}