#include "pch.h"
#include "MonsterCrackScript.h"
#include "Monster.h"
#include "Texture.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Material.h"

namespace hm
{
	MonsterCrackScript::MonsterCrackScript()
	{
	}
	void MonsterCrackScript::FixedUpdate()
	{
		float hpRatio = static_cast<Monster*>(GetGameObject())->GetHPRatio();
		// 크랙 텍스쳐 전달
		shared_ptr<Texture> pCrackTexture = GET_SINGLE(Resources)->Load<Texture>(L"Crack", L"..\\Resources\\Texture\\cracks_generic.png");
		GetMeshRenderer()->GetMaterial()->SetTextureAllSubset(2, pCrackTexture);
		GetMeshRenderer()->GetMaterial()->SetFloatAllSubset(3, hpRatio);

	}
	Component* MonsterCrackScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new MonsterCrackScript);
	}
}