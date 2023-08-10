#include "pch.h"
#include "Light.h"
#include "GameObject.h"
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"
#include "Resources.h"

namespace hm
{
	Light::Light()
		: Component(ComponentType::Light)
		, mLightIndex(-1)
	{
	}
	Light::~Light()
	{
	}
	void Light::FinalUpdate()
	{
		Vec3 worldPos = GetTransform()->GetPosition();
		mLightInfo.position = Vec4(worldPos.x, worldPos.y, worldPos.z, 1.f);
	}
	void Light::Render(Camera* _pCamera)
	{
		AssertEx(mLightIndex >= 0, L"Light::Render() - LightIndex가 지정되지 않음");
		GetTransform()->PushData(_pCamera);

		mpMaterial->SetInt(0, mLightIndex);
		mpMaterial->PushGraphicData();

		switch (static_cast<LightType>(mLightInfo.eLightType))
		{
		case LightType::SpotLight:
		case LightType::PointLight:
			float scale = mLightInfo.range * 2.f;
			GetTransform()->SetScale(Vec3(scale, scale, scale));
			break;
		}

		mpMesh->Render();
	}
	Component* Light::Clone(GameObject* _pGameObject)
	{
		Light* pLight = _pGameObject->AddComponent(new Light);
		pLight->mLightInfo = mLightInfo;
		pLight->mLightIndex = -1;
		pLight->mpMesh = mpMesh;
		pLight->mpMaterial = mpMaterial;

		return pLight;
	}
	void Light::SetLightType(LightType _eLightType)
	{
		mLightInfo.eLightType = static_cast<int>(_eLightType);

		switch (_eLightType)
		{
		case LightType::DirectionalLight:
			mpMesh = GET_SINGLE(Resources)->LoadRectMesh();
			mpMaterial = GET_SINGLE(Resources)->Get<Material>(L"DirLight");
			break;
		case LightType::PointLight:
			mpMesh = GET_SINGLE(Resources)->LoadSphereMesh();
			mpMaterial = GET_SINGLE(Resources)->Get<Material>(L"PointLight");
			break;
		case LightType::SpotLight:
			mpMesh = GET_SINGLE(Resources)->LoadSphereMesh();
			mpMaterial = GET_SINGLE(Resources)->Get<Material>(L"PointLight");
			break;
		}
	}
}

