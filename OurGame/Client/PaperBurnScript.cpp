#include "pch.h"
#include "PaperBurnScript.h"
#include "Timer.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "GameObject.h"
#include "Resources.h"
#include "Texture.h"
#include "Input.h"
#include "EventManager.h"
#include "ChangeMaterialEvent.h"

namespace hm
{
	PaperBurnScript::PaperBurnScript()
		: mAccTime(0.f)
		, mbFlag(false)
		, mbReverseFlag(false)
	{
	}

	PaperBurnScript::~PaperBurnScript()
	{
		mpOrgMat = nullptr;
		mpPaperBurnMat = nullptr;
	}

	void PaperBurnScript::FixedUpdate()
	{
		if (true == mbFlag)
		{
			if (mAccTime < 10.f)
			{
				if (true == mbPaperBurnFinished)
					return;

				mAccTime += DELTA_TIME;
				mpPaperBurnMat->SetFloatAllSubset(0, mbReverseFlag ? 10.0f - mAccTime : mAccTime);

				if (mAccTime > 9.9f)
				{
					mbPaperBurnFinished = true;
					if (mCallback) 
						mCallback();
				}
			}
			else
			{
				mpPaperBurnMat->SetFloatAllSubset(0, mbReverseFlag ? 0.f : 10.f);
				GetMeshRenderer()->SetMaterial(mpOrgMat);
				mbFlag = false;
			}
		}
	}
	Component* PaperBurnScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new PaperBurnScript);
	}
	void PaperBurnScript::Begin()
	{
		if (true == mbFlag)
			return;

		mbPaperBurnFinished = false;
		mAccTime = 0.f;
		mpOrgMat = GetMeshRenderer()->GetMaterial();

		if (nullptr == mpPaperBurnMat)
		{
			mpPaperBurnMat = GET_SINGLE(Resources)->Get<Material>(L"PaperBurn")->Clone();
			mpPaperBurnMat->ClearMaterialContainers();
		}

		UINT32 materialCount = mpOrgMat->GetMaterialContainerCount();
		while (materialCount > mpPaperBurnMat->GetMaterialContainerCount())
		{
			MaterialContainer* pMatContainer = new MaterialContainer;
			pMatContainer->AddSubset(new MaterialSubset);
			mpPaperBurnMat->AddMaterialContainer(pMatContainer);
		}

		for (UINT32 i = 0; i < materialCount; ++i)
		{
			mpPaperBurnMat->SetTexture(0, mpOrgMat->GetTexture(0, i), i);
			mpPaperBurnMat->SetTexture(1, GET_SINGLE(Resources)->Get<Texture>(L"BurnNoise"), i);
		}

		GetMeshRenderer()->SetMaterial(mpPaperBurnMat);
	}
}


