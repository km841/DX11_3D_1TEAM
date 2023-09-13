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

		void Initialize();
		void SetPaperBurn() { Initialize();  mbFlag = true; }
		void SetReverse(bool _bFlag) { mbReverseFlag = _bFlag; }

	private:
		float mAccTime;
		bool mbFlag;
		bool mbReverseFlag;
		wstring mBeforeMatName;
		shared_ptr<Material> mpOrgMat;
		shared_ptr<Material> mpPaperBurnMat;
	};
}


