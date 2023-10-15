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
		, mbPaperBurnFinished(false)
		, mEndTime(6.f)
		, mSpeed(2.f)
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
			if (mAccTime < mEndTime)
			{
				if (true == mbPaperBurnFinished)
				{
					mAccTime = mEndTime;
					return;
				}

				mAccTime += DELTA_TIME * mSpeed;
				mpPaperBurnMat->SetFloatAllSubset(0, mbReverseFlag ? mEndTime - mAccTime : mAccTime);

				if (mAccTime > mEndTime - 0.1f)
				{
					mbPaperBurnFinished = true;
					if (mCallback) 
						mCallback();
				}
			}
			else
			{
				GetMeshRenderer()->SetMaterial(mpOrgMat);
				mbPaperBurnFinished = false;
				mbFlag = false;
				mpPaperBurnMat->SetFloatAllSubset(0, mbReverseFlag ? 0.1f : mEndTime - 0.1f);
			
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
	void PaperBurnScript::SpawnBegin()
	{
		if (true == mbFlag)
			return;

		mbPaperBurnFinished = false;
		mAccTime = 0.f;
		mpOrgMat = GetMeshRenderer()->GetMaterial();

		if (nullptr == mpPaperBurnMat)
		{
			mpPaperBurnMat = GET_SINGLE(Resources)->Get<Material>(L"PaperBurnSpawn")->Clone();
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
	void PaperBurnScript::PotBegin()
	{
		if (true == mbFlag)
			return;

		mbPaperBurnFinished = false;
		mAccTime = 0.f;
		mpOrgMat = GetMeshRenderer()->GetMaterial();

		if (nullptr == mpPaperBurnMat)
		{
			mpPaperBurnMat = GET_SINGLE(Resources)->Get<Material>(L"PaperBurnPot")->Clone();
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


