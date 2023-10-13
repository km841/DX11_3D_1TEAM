#pragma once
#include "MonoBehavior.h"

namespace jh
{
	class TitleSceneCutSceneTargetScript : public MonoBehavior
	{
	public:
		TitleSceneCutSceneTargetScript();
		virtual ~TitleSceneCutSceneTargetScript() = default;
		virtual Component* Clone(GameObject* _pGameObject);

	public:
		virtual void FixedUpdate() override;
	};
}
