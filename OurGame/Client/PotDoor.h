#pragma once
#include "GameObject.h"
#include "TimerObject.h"
namespace hm
{
	class PotDoor :
		public GameObject
	{
	public:
		PotDoor();
		virtual ~PotDoor();
		PotDoor* Clone()
		{
			PotDoor* pDoor = GameObject::Clone<PotDoor>();
			return pDoor;
		}
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

		void CreatedCallback(std::function<void()> _callback) { mCreatedCallback = _callback; }

	public:
		void SetPaperBurn();

	private:
		TimerObject mTimer;
		bool mbIsFinished = false;

		std::function<void()> mCreatedCallback;
	};
}


