#include "pch.h"
#include "TitleSceneCutSceneTargetScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"

namespace jh
{
	TitleSceneCutSceneTargetScript::TitleSceneCutSceneTargetScript()
	{
	}

	Component* TitleSceneCutSceneTargetScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new TitleSceneCutSceneTargetScript);
	}

	void TitleSceneCutSceneTargetScript::FixedUpdate()
	{
		Vec3 pos = GetGameObject()->GetTransform()->GetPosition();
		float speed = 15.f;

		if (IS_PRESS(KeyType::DOWN))
			pos += GetGameObject()->GetTransform()->GetLook() * speed * DELTA_TIME;

		if (IS_PRESS(KeyType::UP))
			pos -= GetGameObject()->GetTransform()->GetLook() * speed * DELTA_TIME;

		if (IS_PRESS(KeyType::RIGHT))
			pos -= GetGameObject()->GetTransform()->GetRight() * speed * DELTA_TIME;

		if (IS_PRESS(KeyType::LEFT))
			pos += GetGameObject()->GetTransform()->GetRight() * speed * DELTA_TIME;

		if (IS_PRESS(KeyType::M))
			pos = Vec3(7.f, -7.f, -6.f);

		GetGameObject()->GetTransform()->SetPosition(pos);
	}
}
