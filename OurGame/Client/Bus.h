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

		void BusActive() { isBusActive = true; }
		bool IsBusArrived() { return mbIsArrived; }

	private:
		void BusEvent();

		bool isBusActive = false;
		int shake;

		int sequenceNum = 0;

		float timer;
		float mAddedDist = 0;

		bool mbIsArrived = false;
	};
}


