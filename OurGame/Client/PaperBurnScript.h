#pragma once
#include "MonoBehavior.h"

namespace hm
{
	class Material;
	class PaperBurnScript :
		public MonoBehavior
	{
	public:
		PaperBurnScript();
		~PaperBurnScript();
		virtual void FixedUpdate() override;

		virtual Component* Clone(class GameObject* _pGameObject);

		void Begin();
		void SpawnBegin();
		void PotBegin();
		void SetPaperBurn() { Begin();  mbFlag = true; }
		void SetSpawnPaperBurn() { SpawnBegin(); mbFlag = true; }
		void SetPotPaperBurn() { PotBegin(); mbFlag = true; }
		void SetReverse(bool _bFlag) { mbReverseFlag = _bFlag; }
		void SetSpeed(float _speed) { mSpeed = _speed; }
		bool IsFinished() { return mbPaperBurnFinished; }
		void SetFinishedCallback(std::function<void()> _func) { mCallback = _func; }
		void Reset() { mbFlag = false; }

	private:
		float mAccTime;
		float mEndTime;
		float mSpeed;
		bool mbFlag;
		bool mbReverseFlag;
		bool mbPaperBurnFinished;
		std::function<void()> mCallback;
		wstring mBeforeMatName;
		shared_ptr<Material> mpOrgMat;
		shared_ptr<Material> mpPaperBurnMat;
	};
}


