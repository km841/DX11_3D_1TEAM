#include "pch.h"
#include "MonsterHitScript.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Material.h"

namespace hm
{
	MonsterHitScript::MonsterHitScript()
	{
		mTimer.SetEndTime(0.3f);
	}

	void MonsterHitScript::FixedUpdate()
	{
		mTimer.Update();

		// Hit °¨Áö
		if (mTimer.GetIsRun())
			GetMeshRenderer()->GetMaterial()->SetFloatAllSubset(2, (1.f - mTimer.GetProgress()));
		
		else
			GetMeshRenderer()->GetMaterial()->SetFloatAllSubset(2, 0.f);
	}

	Component* MonsterHitScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new MonsterHitScript);
	}
	void MonsterHitScript::HitBegin()
	{
		mTimer.Stop();
		mTimer.Start();
	}
}

