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

		void CreatedCallback(std::function<void()> _callback) { mCreatedCallback01 = _callback; }
		void CreatedCallback(std::function<void(int)> _callback, int _a) { mCreatedCallback02 = _callback; a = _a; }
		void CreatedCallback(std::function<void(float)> _callback, float _b) { mCreatedCallback03 = _callback; b = _b; }

	public:
		void SetPaperBurn();

	private:
		TimerObject mTimer;
		bool mbIsFinished = false;

		std::function<void()> mCreatedCallback01;
		std::function<void(int)> mCreatedCallback02;
		std::function<void(float)> mCreatedCallback03;
		int a;
		float b;
	};
}


