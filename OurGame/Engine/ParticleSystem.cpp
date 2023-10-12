#include "pch.h"
#include "ParticleSystem.h"
#include "Resources.h"
#include "StructuredBuffer.h"
#include "Timer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Engine.h"

namespace hm
{
	ParticleSystem::ParticleSystem()
		: Component(ComponentType::ParticleSystem)
		, mpParticleBuffer(nullptr)
		, mpSharedBuffer(nullptr)
		, mMaxParticles(1000)
		, mEndTime(0.3f)
		, mAccTime(0.f)
		, mStartSpeed(1.0f)
		, mEndSpeed(1.0f)
		, mElapsedTime(0.f)
		, mCreateInterval(0.05f)
		, mStartScale(0.5f, 0.5f, 0.5f)
		, mGravity(-1.f)
		, mAliveCount(0)
		, mStartAngle(0.f)
		, mEndAngle(360.f)
		, mStartScaleFloat(1.f)
		, mEndScaleFloat(5.f)
		, mScatterRadius(1.f)
	{
	}

	ParticleSystem::~ParticleSystem()
	{
		SAFE_DELETE(mpParticleBuffer);
		SAFE_DELETE(mpSharedBuffer);
	}

	Component* ParticleSystem::Clone(GameObject* _pGameObject)
	{
		ParticleSystem* pParticleSystem = _pGameObject->AddComponent(new ParticleSystem);
		return pParticleSystem;
	}

	void ParticleSystem::Initialize()
	{
		mpMesh = GET_SINGLE(Resources)->LoadPointMesh();
		mpMaterial = GET_SINGLE(Resources)->Get<Material>(L"Particle");
		mpComputeMaterial = GET_SINGLE(Resources)->Get<Material>(L"ComputeParticle");

		mpMaterial->SetTexture(0, mpParticleTexture);
		mpMaterial->SetTexture(1, mpNoiseTexture);

		std::vector<ParticleInfo> particles(mMaxParticles);
		mpParticleBuffer = new StructuredBuffer;
		mpParticleBuffer->Create(sizeof(ParticleInfo), mMaxParticles, particles.data());

		mpSharedBuffer = new StructuredBuffer;
		mpSharedBuffer->Create(sizeof(ParticleShared), 1, nullptr, true);
	}

	void ParticleSystem::Update()
	{
	}

	void ParticleSystem::FinalUpdate()
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

	void ParticleSystem::Render(Camera* _pCamera)
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

