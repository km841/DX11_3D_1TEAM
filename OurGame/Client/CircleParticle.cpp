#include "pch.h"
#include "CircleParticle.h"
#include "GameObject.h"
#include "Timer.h"
#include "Resources.h"

namespace hm
{
	CircleParticle::CircleParticle()
	{
	}

	CircleParticle::~CircleParticle()
	{
	}

	Component* CircleParticle::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new CircleParticle);
	}

	void CircleParticle::Initialize()
	{
		ParticleSystem::Initialize();
	}

	void CircleParticle::Update()
	{
		ParticleSystem::Update();
	}

	void CircleParticle::FinalUpdate()
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
		mpComputeMaterial->SetFloat(2, mStandardRadius);
		mpComputeMaterial->SetFloat(3, mAllowableRange);
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

	void CircleParticle::Render(Camera* _pCamera)
	{
		ParticleSystem::Render(_pCamera);
	}
}

