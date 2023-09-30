#include "pch.h"
#include "BonFireScript.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Resources.h"
#include "Timer.h"
#include "Engine.h"
#include "SceneManager.h"
#include "Camera.h"

namespace hm
{
	BonFireScript::BonFireScript()
		: mAccTime(0.f)
	{
	}

	Component* BonFireScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new BonFireScript);
	}

	void BonFireScript::FixedUpdate()
	{
		mAccTime += DELTA_TIME;

		GetMeshRenderer()->GetMaterial()->SetTexture(0, GET_SINGLE(Resources)->Load<Texture>(L"FireBurnTex", L"..\\Resources\\Texture\\fire01.dds"));
		GetMeshRenderer()->GetMaterial()->SetTexture(1, GET_SINGLE(Resources)->Load<Texture>(L"FireNoiseTex", L"..\\Resources\\Texture\\noise01.dds"));
		GetMeshRenderer()->GetMaterial()->SetTexture(2, GET_SINGLE(Resources)->Load<Texture>(L"FireAlphaTex", L"..\\Resources\\Texture\\alpha01.dds"));

		Vec3 camPos = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera()->GetTransform()->GetPosition();
		float scale = GetTransform()->GetScale().x;
		GetMeshRenderer()->GetMaterial()->SetVec3(0, camPos);
		GetMeshRenderer()->GetMaterial()->SetFloat(0, scale);
	}
	void BonFireScript::PushData()
	{
		
		NoiseParams noiseParams = {};
		noiseParams.frameTime = mAccTime;
		noiseParams.scrollSpeeds = Vec3(1.3f, 2.1f, 2.3f);
		noiseParams.scales = Vec3(1.f, 2.f, 3.f);
		CONST_BUFFER(ConstantBufferType::Noise)->PushData(&noiseParams, sizeof(NoiseParams));
		CONST_BUFFER(ConstantBufferType::Noise)->Mapping();

		DistortionParams distortionParams = {};
		distortionParams.distortion1 = Vec2(0.1f, 0.2f);
		distortionParams.distortion2 = Vec2(0.1f, 0.3f);
		distortionParams.distortion3 = Vec2(0.1f, 0.1f);
		distortionParams.distortionScale = 0.8f;
		distortionParams.distortionBias = 0.5f;
		CONST_BUFFER(ConstantBufferType::Distortion)->PushData(&distortionParams, sizeof(DistortionParams));
		CONST_BUFFER(ConstantBufferType::Distortion)->Mapping();
	}
}

