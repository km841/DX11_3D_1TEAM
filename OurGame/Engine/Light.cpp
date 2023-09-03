#include "pch.h"
#include "Light.h"
#include "GameObject.h"
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"
#include "Resources.h"
#include "Camera.h"

namespace hm
{
	Light::Light()
		: Component(ComponentType::Light)
		, mLightIndex(-1)
		, mpShadowCamera(nullptr)
	{
	}
	Light::~Light()
	{
	}
	void Light::FinalUpdate()
	{
		if (nullptr != mpShadowCamera)
		{
			GetTransform()->SetRotation(mpShadowCamera->GetTransform()->GetRotation());
			GetTransform()->SetPosition(mpShadowCamera->GetTransform()->GetPosition());
			GetTransform()->SetScale(mpShadowCamera->GetTransform()->GetScale());
		}

		Vec3 worldPos = GetTransform()->GetPosition();
		mLightInfo.position = Vec4(worldPos.x, worldPos.y, worldPos.z, 1.f);

		Vec3 lookDir = mpShadowCamera->GetTransform()->GetLook();
		lookDir.Normalize();
		mLightInfo.direction = lookDir;

	}
	void Light::Render(Camera* _pCamera)
	{
		AssertEx(mLightIndex >= 0, L"Light::Render() - LightIndex가 지정되지 않음");
		GetTransform()->PushData(_pCamera);

		if (LightType::DirectionalLight == static_cast<LightType>(mLightInfo.eLightType))
		{
			Matrix matVP = mpShadowCamera->GetCamera()->GetViewMatrix() * mpShadowCamera->GetCamera()->GetProjectionMatrix();
			mpMaterial->SetMatrix(0, matVP);
		}
		else
		{
			float scale = mLightInfo.range * 2.f;
			GetTransform()->SetScale(Vec3(scale, scale, scale));
		}

		mpMaterial->SetInt(0, mLightIndex);
		mpMaterial->PushGraphicData();
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
	void Light::RenderStaticShadow()
	{
		mpShadowCamera->GetCamera()->SortStaticShadowObject();
		mpShadowCamera->GetCamera()->RenderShadow();

	}
	void Light::RenderDynamicShadow()
	{
		mpShadowCamera->GetCamera()->SortDynamicShadowObject();
		mpShadowCamera->GetCamera()->RenderShadow();
	}
	void Light::SetLightDirection(Vec3 _direction)
	{
		_direction.Normalize();
		mLightInfo.direction = _direction;

		GetTransform()->LookAt(_direction);
	}
	void Light::SetLightType(LightType _eLightType)
	{
		mLightInfo.eLightType = static_cast<int>(_eLightType);

		switch (_eLightType)
		{
		case LightType::DirectionalLight:
			mpMesh = GET_SINGLE(Resources)->LoadRectMesh();
			mpMaterial = GET_SINGLE(Resources)->Get<Material>(L"DirLight");
			mpShadowCamera->GetCamera()->SetScale(1.f);
			mpShadowCamera->GetCamera()->SetFar(10000.f);
			mpShadowCamera->GetCamera()->SetWidth(4096.f);
			mpShadowCamera->GetCamera()->SetHeight(4096.f);


			break;
		case LightType::PointLight:
		case LightType::SpotLight:
			mpMesh = GET_SINGLE(Resources)->LoadSphereMesh();
			mpMaterial = GET_SINGLE(Resources)->Get<Material>(L"PointLight");
			break;
		}
	}

	void Light::SetShadowCamera(GameObject* _pShadowCamera)
	{
		mpShadowCamera = _pShadowCamera;
	}
}

