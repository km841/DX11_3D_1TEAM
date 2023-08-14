#include "pch.h"
#include "PaperBurnScript.h"
#include "Timer.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "GameObject.h"

namespace hm
{
	PaperBurnScript::PaperBurnScript()
		: mAccTime(0.f)
	{
	}

	void PaperBurnScript::FixedUpdate()
	{
		mAccTime += DELTA_TIME;
		GetMeshRenderer()->GetMaterial()->SetFloatAllSubset(0, mAccTime);
	}
	Component* PaperBurnScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new PaperBurnScript);
	}
}


