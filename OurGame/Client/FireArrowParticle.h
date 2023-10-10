#pragma once
#include "ParticleSystem.h"

namespace hm
{
	class FireArrowParticle :
		public ParticleSystem
	{
	public:
		FireArrowParticle();
		~FireArrowParticle();

		virtual Component* Clone(GameObject* _pGameObject);

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FinalUpdate() override;
		virtual void Render(Camera* _pCamera);
	};

}

