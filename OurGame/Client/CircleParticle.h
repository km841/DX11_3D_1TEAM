#pragma once
#include "ParticleSystem.h"

namespace hm
{
	class CircleParticle :
		public ParticleSystem
	{
	public:
		CircleParticle();
		~CircleParticle();

		virtual Component* Clone(GameObject* _pGameObject);

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FinalUpdate() override;
		virtual void Render(Camera* _pCamera);

	public:
		void SetStandardRadius(float _radius) { mStandardRadius = _radius; }
		void SetAllowableRange(float _range) { mAllowableRange = _range; }

	private:
		float mStandardRadius;
		float mAllowableRange;
	};
}


