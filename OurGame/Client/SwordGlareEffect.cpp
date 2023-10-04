#include "pch.h"
#include "SwordGlareEffect.h"
#include "SlashGlareScript.h"
#include "Factory.h"
#include "Transform.h"
#include "SceneManager.h"
#include "EventManager.h"


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
		pEffect->GetTransform()->SetScale(Vec3(2.f, 1.f, 4.f));

		static std::mt19937 engine((unsigned int)time(NULL));                    // MT19937 난수 엔진
		static std::uniform_int_distribution<int> distribution(0, 7);          // 생성 범위
		static auto generator = std::bind(distribution, engine);

		static float anglesY[] = { -70.f, -50.f, -30.f, -10.f, 10.f, 30.f, 50.f, 70.f};
		static float anglesX[] = { 5.f, 10.f, 15.f, 20.f, 25.f, 30.f, 35.f };
		pEffect->GetTransform()->SetRotation(AXIS_X, anglesX[generator()]);
		pEffect->GetTransform()->SetRotation(AXIS_Y, anglesY[generator()]);
		
		SlashGlareScript* pScript = pEffect->AddComponent(new SlashGlareScript);
		
		pScript->SetEndCallback([=]() 
			{ 
				SceneType eSceneType = GET_SINGLE(SceneManager)->GetActiveSceneType();
				GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(eSceneType, pEffect);
			});
		pScript->Start();

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pEffect);
		
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

