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
				mAccTime += DELTA_TIME;
				mpPaperBurnMat->SetFloatAllSubset(0, mbReverseFlag ? 10.0f - mAccTime : mAccTime);
			}
			else
			{
				GetMeshRenderer()->SetMaterial(mpOrgMat);
				mbFlag = false;
			}
		}
	}
	Component* PaperBurnScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new PaperBurnScript);
	}
	void PaperBurnScript::Initialize()
	{
		if (true == mbFlag)
			return;

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


