#include "pch.h"
#include "SpiderWeb.h"
#include "Collider.h"
#include "MeshRenderer.h"
#include "Input.h"
#include "Material.h"
#include "Timer.h"
#include "Texture.h"
#include "Resources.h"
#include "ArrowScript.h"

namespace hm
{
	SpiderWeb::SpiderWeb()
		: GameObject(LayerType::Obstacle)
		, mBurn(false)
	{
		mTimer.SetEndTime(3.f);
		
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

		if (1 == mBurn)
			mTimer.Update();
		
		GetMeshRenderer()->GetMaterial()->SetFloatAllSubset(0, mTimer.GetCurTime());
		GetMeshRenderer()->GetMaterial()->SetIntAllSubset(3, mBurn);
		GetMeshRenderer()->GetMaterial()->SetTexture(1, GET_SINGLE(Resources)->Get<Texture>(L"BurnNoise"));
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
			ArrowScript* pScript = _pOtherCollider->GetGameObject()->GetScript<ArrowScript>();
			if (nullptr != pScript && true == pScript->GetIsBurn())
			{
				mBurn = 1;
				mTimer.Start();
			}
		}
	}
	void SpiderWeb::OnTriggerStay(Collider* _pOtherCollider)
	{
	}
	void SpiderWeb::OnTriggerExit(Collider* _pOtherCollider)
	{
	}
}