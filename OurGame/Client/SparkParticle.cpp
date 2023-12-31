#include "pch.h"
#include "SparkParticle.h"
#include "Material.h"
#include "Timer.h"
#include "GameObject.h"
#include "Resources.h"

namespace hm
{
	SparkParticle::SparkParticle()
	{
		mMaxParticles = 1000;
		mEndTime = 0.1f;
		mAccTime = 0.f;
		mStartSpeed = 30.0f;
		mEndSpeed = 35.0f;
		mElapsedTime = 0.f;
		mCreateInterval = 0.05f;
		mStartScale = Vec3(2.f, 2.f, 1.f);
		mGravity = -50.f;
		mAliveCount = 0;
		mStartAngle = 0.f;
		mEndAngle = 360.f;
		mStartScaleFloat = 0.5f;
		mEndScaleFloat = 0.5f;
	}
	SparkParticle::~SparkParticle()
	{
	}
	Component* SparkParticle::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new SparkParticle);
	}
	void SparkParticle::Initialize()
	{
		mpParticleTexture = GET_SINGLE(Resources)->Load<Texture>(L"SampleParticle", L"..\\Resources\\Texture\\ParticleSample2.png");

		mpMesh = GET_SINGLE(Resources)->LoadPointMesh();
		mpMaterial = GET_SINGLE(Resources)->Get<Material>(L"SparkParticle");
		mpComputeMaterial = GET_SINGLE(Resources)->Get<Material>(L"ComputeParticle_Spark");

		mpMaterial->SetTexture(0, mpParticleTexture);
		mpMaterial->SetTexture(1, mpNoiseTexture);

		std::vector<ParticleInfo> particles(mMaxParticles);
		mpParticleBuffer = new StructuredBuffer;
		mpParticleBuffer->Create(sizeof(ParticleInfo), mMaxParticles, particles.data());

		mpSharedBuffer = new StructuredBuffer;
		mpSharedBuffer->Create(sizeof(ParticleShared), 1, nullptr, true);
	}
	void SparkParticle::Update()
	{
		ParticleSystem::Update();
	}
	void SparkParticle::FinalUpdate()
	{
		mElapsedTime += DELTA_TIME;
		mAccTime += DELTA_TIME;

		if (true == GetGameObject()->IsEnable())
		{
			mAccTime += DELTA_TIME;
			if (mCreateInterval < mAccTime)
			{
				mAliveCount = 1;
				mAccTime = 0.f;
			}
		}

		if (mAliveCount > 0)
		{
			ParticleShared shared = { mAliveCount, }; // 활성화시킬 파티클의 수
			mpSharedBuffer->SetData(&shared, 1);
			mAliveCount = 0;

			mAccTime = 0.f;
		}

		else
		{
			ParticleShared shared = {  };
			mpSharedBuffer->SetData(&shared, 1);
		}

		Vec3 vPosition = GetGameObject()->GetTransform()->GetPosition();
		mMaxParticles = mpParticleBuffer->GetElementCount();
		mpComputeMaterial->SetInt(0, mMaxParticles);
		mpComputeMaterial->SetFloat(0, mEndTime);
		mpComputeMaterial->SetFloat(1, mGravity);
		mpComputeMaterial->SetFloat(2, mScatterRadius);
		mpComputeMaterial->SetVec2(0, Vec2(DELTA_TIME, mElapsedTime));
		mpComputeMaterial->SetVec2(1, Vec2(mStartSpeed, mEndSpeed));
		mpComputeMaterial->SetVec2(2, Vec2(mStartAngle, mEndAngle));
		mpComputeMaterial->SetVec2(3, Vec2(mStartScaleFloat, mEndScaleFloat));
		mpComputeMaterial->SetVec4(0, Vec4(vPosition.x, vPosition.y, vPosition.z, 1.f));
		mpComputeMaterial->SetVec4(1, Vec4(mStandardAngle.x, mStandardAngle.y, mStandardAngle.z, 1.f));
		mpComputeMaterial->SetVec4(2, Vec4(mStartColor.x, mStartColor.y, mStartColor.z, 1.f));
		mpComputeMaterial->SetVec4(3, Vec4(mEndColor.x, mEndColor.y, mEndColor.z, 1.f));

		mpParticleBuffer->PushComputeUAVData(RegisterUAV::u0);
		mpSharedBuffer->PushComputeUAVData(RegisterUAV::u1);
		mpComputeMaterial->Dispatch(1, 1, 1);
	}
	void SparkParticle::Render(Camera* _pCamera)
	{
		GetGameObject()->GetTransform()->PushData(_pCamera);
		mpParticleBuffer->PushGraphicsData(RegisterSRV::t9);

		mpMaterial->GetShader()->SetSamplerType(SamplerType::Clamp);
		mpMaterial->SetVec4(0, Vec4(mStartScale.x, mStartScale.y, mStartScale.z, 0.f));
		mpMaterial->SetVec4(1, Vec4(mParticleRotation.x, mParticleRotation.y, mParticleRotation.z, 0.f));
		mpMaterial->PushGraphicDataExceptForTextures();

		mpParticleTexture->PushSRV(RegisterSRV::t0);
		if (nullptr != mpNoiseTexture)
			mpNoiseTexture->PushSRV(RegisterSRV::t1);

		CONST_BUFFER(ConstantBufferType::Material)->Mapping();
		mpMesh->RenderInstancing(mMaxParticles);

		mpParticleBuffer->ClearGraphicsData();
	}
}