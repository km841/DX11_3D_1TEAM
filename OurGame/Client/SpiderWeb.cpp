#include "pch.h"
#include "SpiderWeb.h"
#include "Collider.h"

namespace hm
{
	SpiderWeb::SpiderWeb()
		: GameObject(LayerType::Obstacle)
	{
	}
	SpiderWeb::~SpiderWeb()
	{
	}
	void SpiderWeb::Initialize()
	{
		GameObject::Initialize();
	}
	void SpiderWeb::Update()
	{
		GameObject::Update();
	}
	void SpiderWeb::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void SpiderWeb::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}
	void SpiderWeb::Render()
	{
		GameObject::Render();
	}
	void SpiderWeb::Destroy()
	{
		GameObject::Destroy();
	}
	void SpiderWeb::OnCollisionEnter(Collider* _pOtherCollider)
	{
	}
	void SpiderWeb::OnCollisionStay(Collider* _pOtherCollider)
	{
	}
	void SpiderWeb::OnCollisionExit(Collider* _pOtherCollider)
	{
	}
	void SpiderWeb::OnTriggerEnter(Collider* _pOtherCollider)
	{
		if (LayerType::ArrowCol == _pOtherCollider->GetGameObject()->GetLayerType())
		{
			int a = 0;
		}
	}
	void SpiderWeb::OnTriggerStay(Collider* _pOtherCollider)
	{
	}
	void SpiderWeb::OnTriggerExit(Collider* _pOtherCollider)
	{
	}
}