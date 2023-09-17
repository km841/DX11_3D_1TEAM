#pragma once
#include "GameObject.h"
namespace yj
{

	class Bus : public GameObject
	{
	public:
		//virtual void Update();
		Bus();
		virtual ~Bus();
		Bus* Clone()
		{
			Bus* pBus = GameObject::Clone<Bus>();
			return pBus;
		}

		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

		void Shake();

		enum Sequence
		{
			Stanby,
			Move,
			Wait,
			End
		};
		Sequence sequence;
	private:

		int shake;

		Vec3 mOriginPos;

		float stopX;
	};
}