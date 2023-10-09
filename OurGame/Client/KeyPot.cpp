#include "pch.h"
#include "KeyPot.h"

#include "Rigidbody.h"
#include "Collider.h"
#include "Input.h"

#include "SceneManager.h"
#include "Scene.h"

namespace yj
{
	KeyPot::KeyPot()
		:GameObject(LayerType::DungeonObject)
	{
	}
	KeyPot::~KeyPot()
	{
	}
	void KeyPot::Initialize()
	{
		GameObject::Initialize();
	}
	void KeyPot::Update()
	{
		GameObject::Update();
		if (pReceiver == nullptr)
		{
			return;
		}


		if (mBreakSequence > 0)
		{
			Break();
		}

		if (IS_DOWN(KeyType::R))
		{
			pReceiver->AddKey();
			mBreakSequence = 1;
			isBreak = true;
		}

	}
	void KeyPot::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void KeyPot::Render()
	{
		GameObject::Render();
	}
	void KeyPot::SetReceiver(JarDoor* _receiver)
	{
		pReceiver = _receiver;
	}
	void KeyPot::CheckHitBySword()
	{

	}
	void KeyPot::Break()
	{
		//¾Ö´Ï¸ÞÀÌ¼Ç Àç»ý ÈÄ
		//mBreakSequence = 0;
	}
	void KeyPot::OnTriggerEnter(Collider* _pOther)
	{
		if (LayerType::PlayerCol == _pOther->GetGameObject()->GetLayerType() || 
			LayerType::ArrowCol == _pOther->GetGameObject()->GetLayerType())
		{
			if (false == isBreak)
			{
				pReceiver->AddKey();
				mBreakSequence = 0;
				isBreak = true;
				this->Disable();
			}
		}
	}
	void KeyPot::OnTriggerStay(Collider* _pOther)
	{
	}
	void KeyPot::OnTriggerExit(Collider* _pOther)
	{
	}
}