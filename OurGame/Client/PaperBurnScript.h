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
		void SetPaperBurn() { Begin();  mbFlag = true; }
		void SetReverse(bool _bFlag) { mbReverseFlag = _bFlag; }
		bool IsFinished() { return mbPaperBurnFinished; }
		void SetFinishedCallback(std::function<void()> _func) { mCallback = _func; }

	private:
		float mAccTime;
		bool mbFlag;
		bool mbReverseFlag;
		bool mbPaperBurnFinished;
		std::function<void()> mCallback;
		wstring mBeforeMatName;
		shared_ptr<Material> mpOrgMat;
		shared_ptr<Material> mpPaperBurnMat;
	};
}


