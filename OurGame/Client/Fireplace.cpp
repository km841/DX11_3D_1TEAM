#include "pch.h"
#include "Fireplace.h"
#include "GameObject.h"
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"
#include "Resources.h"
#include "Camera.h"
#include "Engine.h"
#include "SceneManager.h"

namespace hm
{
	Fireplace::Fireplace()
	{
	}

	Fireplace::~Fireplace()
	{
	}

	void Fireplace::FinalUpdate()
	{
		if (nullptr != mpShadowCamera)
		{
			mpShadowCamera->GetCamera()->SetFov(110.f * XM_PI / 180.f);
			Vec3 camPos = GetTransform()->GetPosition();

			mpShadowCamera->GetTransform()->SetRotation(GetTransform()->GetRotation());
			mpShadowCamera->GetTransform()->SetPosition(camPos);
			mpShadowCamera->GetTransform()->SetScale(GetTransform()->GetScale());
			mpShadowCamera->FinalUpdate();
		}

		Vec3 worldPos = GetTransform()->GetPosition();
		mLightInfo.position = Vec4(worldPos.x, worldPos.y, worldPos.z, 1.f);

		Vec3 lookDir = mpShadowCamera->GetTransform()->GetLook();
		lookDir.Normalize();
		mLightInfo.direction = lookDir;
	}

	void Fireplace::Render(Camera* _pCamera)
	{
		if (false == GetGameObject()->IsEnable())
			return;

		AssertEx(mLightIndex >= 0, L"Light::Render() - LightIndex가 지정되지 않음");

		GetTransform()->PushData(_pCamera);

		Matrix matVP = mpShadowCamera->GetCamera()->GetViewMatrix() * mpShadowCamera->GetCamera()->GetProjectionMatrix();
		mpMaterial->SetMatrix(0, matVP);

		if (LightType::DirectionalLight != static_cast<LightType>(mLightInfo.eLightType))
		{
			float scale = mLightInfo.range * 2.f;
			GetTransform()->SetScale(Vec3(scale, scale, scale));
		}

		mpMaterial->SetTexture(2, mpStaticShadowMap);
		mpMaterial->SetTexture(3, mpDynamicShadowMap);

		mpMaterial->SetInt(0, mLightIndex);
		mpMaterial->PushGraphicData();
		mpMesh->Render();
	}

	Component* Fireplace::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new Fireplace);
	}
}

