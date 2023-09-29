#include "pch.h"
#include "InterfaceAlphaScript.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Mesh.h"

namespace hm
{
	InterfaceAlphaScript::InterfaceAlphaScript()
		: mAlpha(1.f)
	{
	}

	void InterfaceAlphaScript::FixedUpdate()
	{
		GetMeshRenderer()->GetMaterial()->SetFloatAllSubset(3, mAlpha);
	}

	Component* InterfaceAlphaScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new InterfaceAlphaScript);
	}
}

