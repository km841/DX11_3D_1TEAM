#include "pch.h"
#include "FireArrowParticle.h"
#include "Material.h"
#include "Timer.h"
#include "GameObject.h"
#include "Resources.h"

namespace hm
{
	FireArrowParticle::FireArrowParticle()
	{
		mMaxParticles = 1000;
		mEndTime = 0.3f;
		mAccTime = 0.f;
		mStartSpeed = 1.0f;
		mEndSpeed = 1.0f;
		mElapsedTime = 0.f;
		mCreateInterval = 0.0005f;
		mStartScale = Vec3(0.5f, 0.5f, 0.5f);
		mGravity = -0.1f;
		mAliveCount = 0;
		mStartAngle = 0.f;
		mEndAngle = 360.f;
		mStartScaleFloat = 1.f;
		mEndScaleFloat = 5.f;


	}

	FireArrowParticle::~FireArrowParticle()
	{
	}

	Component* FireArrowParticle::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new FireArrowParticle);
	}

	void FireArrowParticle::Initialize()
	{
		mpParticleTexture = GET_SINGLE(Resources)->Load<Texture>(L"ArrowTexture", L"..\\Resources\\Texture\\Default-ParticleSystem.png");
		ParticleSystem::Initialize();


	}

	void FireArrowParticle::Update()
	{
		ParticleSystem::Update();
	}

	void FireArrowParticle::FinalUpdate()
	{
		ParticleSystem::FinalUpdate();
	}

	void FireArrowParticle::Render(Camera* _pCamera)
	{
		ParticleSystem::Render(_pCamera);
	}
}