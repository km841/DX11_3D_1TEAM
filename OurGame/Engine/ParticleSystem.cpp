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
		, mEndTime(1.f)
		, mAccTime(0.f)
		, mStartSpeed(5.0f)
		, mEndSpeed(15.f)
		, mElapsedTime(0.f)
		, mCreateInterval(0.05f)
		, mStartScale(2.f, 2.f, 2.f)
		, mGravity(-0.1f)
		, mAliveCount(0)
		, mStartAngle(0.f)
		, mEndAngle(360.f)
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

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"Bubble", L"..\\Resources\\Texture\\bubble.png");
		mpMaterial->SetTexture(0, pTexture);

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

		if (mCreateInterval < mAccTime)
		{
			mAliveCount = 1;
			mAccTime = 0.f;
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
		mpComputeMaterial->SetVec4(0, Vec4(vPosition.x, vPosition.y, vPosition.z, 1.f));
		mpComputeMaterial->SetVec4(1, Vec4::Zero);
		mpComputeMaterial->SetInt(0, mMaxParticles);
		mpComputeMaterial->SetFloat(0, mEndTime);
		mpComputeMaterial->SetFloat(1, mGravity);
		mpComputeMaterial->SetVec2(0, Vec2(DELTA_TIME, mElapsedTime));
		mpComputeMaterial->SetVec2(1, Vec2(mStartSpeed, mEndSpeed));
		mpComputeMaterial->SetVec2(2, Vec2(mStartAngle, mEndAngle));

		mpParticleBuffer->PushComputeUAVData(RegisterUAV::u0);
		mpSharedBuffer->PushComputeUAVData(RegisterUAV::u1);
		mpComputeMaterial->Dispatch(1, 1, 1);
	}

	void ParticleSystem::Render(Camera* _pCamera)
	{
		GetGameObject()->GetTransform()->PushData(_pCamera);
		mpParticleBuffer->PushGraphicsData(RegisterSRV::t9);

		mpMaterial->SetVec4(0, Vec4(mStartScale.x, mStartScale.y, mStartScale.z, 0.f));
		mpMaterial->PushGraphicDataExceptForTextures();

		GET_SINGLE(Resources)->Get<Texture>(L"Bubble")->PushSRV(RegisterSRV::t0);
		CONST_BUFFER(ConstantBufferType::Material)->Mapping();
		mpMesh->RenderInstancing(mMaxParticles);

		mpParticleBuffer->ClearGraphicsData();
	}

}

