#include "pch.h"
#include "SwordGlareEffect.h"
#include "SlashGlareScript.h"
#include "Factory.h"
#include "Transform.h"


namespace hm
{
	SwordGlareEffect::SwordGlareEffect()
	{
	}

	SwordGlareEffect::~SwordGlareEffect()
	{
	}

	SwordGlareEffect* SwordGlareEffect::Create(const Vec3& _pos)
	{
		SwordGlareEffect* pEffect = Factory::CreateObject<SwordGlareEffect>(_pos, L"SlashGlare", L"..\\Resources\\FBX\\Player\\Slash_Glare.fbx");
		pEffect->GetTransform()->SetScale(Vec3(2.5f, 1.f, 5.f));
		
		SlashGlareScript* pScript = pEffect->AddComponent(new SlashGlareScript);
		pScript->SetEndCallback([=]() { delete pEffect; });
		pScript->Start();
		
		return pEffect;
	}

	void SwordGlareEffect::Initialize()
	{
		Effect::Initialize();
	}

	void SwordGlareEffect::Update()
	{
		Effect::Update();
	}

	void SwordGlareEffect::FixedUpdate()
	{
		Effect::FixedUpdate();
	}

	void SwordGlareEffect::FinalUpdate()
	{
		Effect::FinalUpdate();
	}

	void SwordGlareEffect::Render()
	{
		Effect::Render();
	}

	void SwordGlareEffect::Destroy()
	{
		Effect::Destroy();
	}
}

