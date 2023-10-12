#pragma once
#include "Component.h"
#include "StructuredBuffer.h"
namespace hm
{
	class Material;
	class Mesh;
	class Camera;
	class Texture;

	struct ParticleInfo
	{
		Vec3 position;
		float endTime;
		Vec3 direction;
		float curTime;

		Vec3 startColor;
		float padd1;
		Vec3 endColor;
		float padd2;

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

		virtual Component* Clone(GameObject* _pGameObject);

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
		void SetMiddleColor(const Vec3& _color) { mMiddleColor = _color; }
		void SetStartColor(const Vec3& _color) { mStartColor = _color; }
		void SetEndColor(const Vec3& _color) { mEndColor = _color; }
		void SetAliveCount(const UINT32 _count) { mAliveCount = _count; }
		void SetParticleRotation(const Vec3& _rotation) { mParticleRotation = _rotation; }

		void SetAngle(const Vec3& _angle) { mStandardAngle = _angle; }
		void SetScatterRadius(float _radius) { mScatterRadius = _radius; }

		void SetParticleTexture(shared_ptr<Texture> _pTexture) { mpParticleTexture = _pTexture; }
		void SetNoiseTexture(shared_ptr<Texture> _pTexture) { mpNoiseTexture = _pTexture; }

	protected:
		StructuredBuffer* mpParticleBuffer;
		StructuredBuffer* mpSharedBuffer;

		shared_ptr<Mesh> mpMesh;
		shared_ptr<Material> mpMaterial;
		shared_ptr<Material> mpComputeMaterial;

		shared_ptr<Texture> mpParticleTexture;
		shared_ptr<Texture> mpNoiseTexture;

		Vec3 mStartScale;
		Vec3 mStartDir;
		Vec3 mStartColor;
		Vec3 mEndColor;
		Vec3 mMiddleColor;
		Vec3 mStandardAngle;
		Vec3 mParticleRotation;

		float mGravity;

		UINT mAliveCount;
		UINT mMaxParticles;
		float mEndTime;
		float mStartSpeed;
		float mEndSpeed;

		float mStartAngle;
		float mEndAngle;

		float mStartScaleFloat;
		float mEndScaleFloat;

		float mElapsedTime;
		float mAccTime;

		float mCreateInterval;
		float mScatterRadius;


	};
}

