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
		:GameObject(LayerType::DecoObject)
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
		if (!isBreak)
		{
				if (this->GetRigidBody()->GetCollider()->CheckIsCollisionObject(LayerType::Item))
				{
					pReceiver->GetScript<JarDoor>()->AddKey();
					mBreakSequence = 0;
					isBreak = true;
				}
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

		//애니메이션 재생 후
		//mBreakSequence = 0;
	}
}