#pragma once

#include "GameObject.h"

namespace yj
{
	class HeadText : public MonoBehavior
	{
	public:

		HeadText();
		virtual ~HeadText();
		virtual void Initialize();
		virtual void Update();
		virtual Component* Clone(GameObject* _pGameObject);

	public:
		void SetDectetorPos(Vec3 _pos) { pDetector->GetTransform()->SetPosition(_pos); }
	public:

		enum State
		{
			Start,
			Apear,
			Disapear,
			Standby,
			End
		};
		State mState;
	private:

		void Increase();
		void Decrease();

		Vec3 mMaxSize;
		float mSpeed;


		GameObject* pDetector;
		GameObject* pTextObj;

	};
}