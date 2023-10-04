#include "pch.h"

#include "TeleportZone.h"

#include "RigidBody.h"
#include "Collider.h"

#include "RenderManager.h"
#include "EventManager.h"

#include "Player.h"
#include "PlayerMoveOverMapScript.h"

namespace yj
{
	TeleportZone::TeleportZone(MapType _mMapType)
		:GameObject(LayerType::Portal),
		mMapType(_mMapType)
	{

	}

	TeleportZone::~TeleportZone()
	{
	}

	void TeleportZone::Update()
	{
		GameObject::Update();
		if (!isActive)
		{
			if (CheckPlayerIn())
			{
				GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeIn, 1,
					nullptr, std::bind(&TeleportZone::ChangeScene, this));
				isActive = true;
			}
		}
	}


	bool TeleportZone::CheckPlayerIn()
	{
		if (this->GetRigidBody()->GetCollider()->CheckIsCollisionObject(LayerType::Player))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void TeleportZone::ChangeScene()
	{
		GET_SINGLE(EventManager)->PushSceneChangeEvent(mMapType);
		//PLAYER->GetScript<PlayerMoveOverMapScript>()->SetMoveOverNum(0);
	}
}