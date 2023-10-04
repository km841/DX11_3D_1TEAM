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

		// Hit °¨Áö
		if (true == mTimer.GetIsRun())
		{
			mTimer.Update();
			GetMeshRenderer()->GetMaterial()->SetIntAllSubset(3, 1);
			GetMeshRenderer()->GetMaterial()->SetFloatAllSubset(2, (1.f - mTimer.GetProgress()));
		}

		
		if (true == mTimer.IsFinished())
		{
			GetMeshRenderer()->GetMaterial()->SetIntAllSubset(3, 0);
			GetMeshRenderer()->GetMaterial()->SetFloatAllSubset(2, 0.f);
			mTimer.Stop();
		}
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

