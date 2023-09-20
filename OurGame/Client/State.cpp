#include "pch.h"
#include "State.h"
#include "Collider.h"
#include "Ground.h"
#include "SceneManager.h"
#include "RigidBody.h"
#include "Transform.h"

State::State(PlayerState _mePlayerState)
	: mePlayerState(_mePlayerState)
{
	mTimerObj.push_back(TimerObject());

}

void State::Update()
{
}

void State::Enter()
{
}

void State::Exit()
{
}

void State::PlayAnimation()
{
}

bool State::IsGround()
{
	Vec3 scale = PLAYER->GetRigidBody()->GetGeometrySize();
	Vec3 pos = PLAYER->GetTransform()->GetPosition();
	Vec3 footPos = pos;
	footPos.y -= scale.y / 2.f;

	Vec3 btmDir = Vec3(0.f, -1.f, 0.f);
	Collider* pCollider = PLAYER->GetCollider();

	const std::vector<GameObject*>& gameObjects = GET_SINGLE(SceneManager)->GetActiveScene()->GetGameObjects(LayerType::Ground);

	for (GameObject* pGameObject : gameObjects)
	{
		if (nullptr != pGameObject->GetCollider())
		{
			return pCollider->Raycast(footPos, btmDir, pGameObject->GetCollider(), 0.1f);
		}
	}

	return false;
}
