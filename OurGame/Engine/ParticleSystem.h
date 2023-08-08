#pragma once
#include "Component.h"
namespace hm
{
	class Material;
	class Mesh;
	class Camera;
	class StructuredBuffer;

	struct ParticleInfo
	{
		Vec3 position;
		float endTime;
		Vec3 direction;
		float curTime;

		float speed;
		Vec2 gravityAcc;
		UINT alive;
	};

	struct ParticleShared
	{
		UINT add;
	};

	class ParticleSystem :
		public Component
	{
	public:
		ParticleSystem();
		~ParticleSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FinalUpdate() override;
		virtual void Render(Camera* _pCamera);

	public:
		void SetParticleAliveCount(UINT _count) { mAliveCount = _count; }
		void SetParticleScale(const Vec3& _scale) { mStartScale = _scale; }
		void SetParticleLifeTime(float _lifeTime) { mEndTime = _lifeTime; }
		void SetCreateInterval(float _createInterval) { mCreateInterval = _createInterval; }
		void SetMaxParticles(UINT _maxParticles) { mMaxParticles = _maxParticles; }


	private:
		StructuredBuffer* mpParticleBuffer;
		StructuredBuffer* mpSharedBuffer;

		shared_ptr<Mesh> mpMesh;
		shared_ptr<Material> mpMaterial;
		shared_ptr<Material> mpComputeMaterial;

		Vec3 mStartScale;
		Vec3 mStartDir;

		float mGravity;

		UINT mAliveCount;
		UINT mMaxParticles;
		float mEndTime;
		float mStartSpeed;
		float mEndSpeed;

		float mStartAngle;
		float mEndAngle;

		float mElapsedTime;
		float mAccTime;

		float mCreateInterval;

	};
}

