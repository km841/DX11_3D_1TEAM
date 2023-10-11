#pragma once
#include "ParticleSystem.h"

namespace hm
{
	class SparkParticle :
		public ParticleSystem
	{
	public:
		SparkParticle();
		~SparkParticle();

		virtual Component* Clone(GameObject* _pGameObject);

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FinalUpdate() override;
		virtual void Render(Camera* _pCamera);
	};

}

