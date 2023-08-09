#include "pch.h"
#include "RenderManager.h"
#include "Engine.h"
#include "SceneManager.h"
#include "Light.h"
#include "Camera.h"
#include "Resources.h"
#include "ImageFilter.h"
#include "BlurFilter.h"
#include "CombineFilter.h"
#include "MeshRenderer.h"
#include "Transform.h"

namespace hm
{
	RenderManager::RenderManager()
	{
	}

	RenderManager::~RenderManager()
	{
		for (auto& pair : mBuffers)
		{
			InstancingBuffer* buffer = pair.second;
			SAFE_DELETE(buffer);
		}
	}

	void RenderManager::Initialize()
	{
	}

	void RenderManager::Render(Scene* _pScene)
	{
		ClearInstancingBuffer();

		PushLightData(_pScene);
		SortGameObject(_pScene);

		RenderDeferred(_pScene);
		RenderLight(_pScene);
		RenderFinal(_pScene);
		RenderForward(_pScene);

		//PostProcessing(_pScene);
	}

	void RenderManager::ClearInstancingBuffer()
	{
		for (auto& pair : mBuffers)
		{
			InstancingBuffer* buffer = pair.second;
			buffer->ClearData();
		}
	}

	void RenderManager::Clear()
	{
		mBuffers.clear();
	}

	void RenderManager::ClearRenderTargets()
	{
		gpEngine->GetMultiRenderTarget(MultiRenderTargetType::SwapChain)->ClearRenderTargetView();
		gpEngine->GetMultiRenderTarget(MultiRenderTargetType::G_Buffer)->ClearRenderTargetView();
		gpEngine->GetMultiRenderTarget(MultiRenderTargetType::Light)->ClearRenderTargetView();
	}

	void RenderManager::SortGameObject(Scene* _pScene)
	{
		AssertEx(_pScene->mpMainCamera, L"RenderManager::SortGameObject() - MainCamera is empty");
		_pScene->mpMainCamera->GetCamera()->SortGameObject();

		for (GameObject* pCameraObject : _pScene->mCameraObjects)
		{
			if (pCameraObject == _pScene->mpMainCamera)
				continue;

			pCameraObject->GetCamera()->SortGameObject();
		}
	}

	void RenderManager::RenderForward(Scene* _pScene)
	{
		gpEngine->GetMultiRenderTarget(MultiRenderTargetType::SwapChain)->OMSetRenderTarget(1);
		RenderInstancing(_pScene->mpMainCamera->GetCamera(), _pScene->mpMainCamera->GetCamera()->GetForwardObjects());
		_pScene->mpMainCamera->GetCamera()->RenderParticle();

		for (GameObject* pCameraObject : _pScene->mCameraObjects)
		{
			if (pCameraObject == _pScene->mpMainCamera)
				continue;
			
			RenderInstancing(pCameraObject->GetCamera(), pCameraObject->GetCamera()->GetForwardObjects());
			pCameraObject->GetCamera()->RenderParticle();
		}
	}

	void RenderManager::RenderDeferred(Scene* _pScene)
	{
		gpEngine->GetMultiRenderTarget(MultiRenderTargetType::G_Buffer)->OMSetRenderTarget();
		RenderInstancing(_pScene->mpMainCamera->GetCamera(), _pScene->mpMainCamera->GetCamera()->GetDeferredObjects());

		for (GameObject* pCameraObject : _pScene->mCameraObjects)
		{
			if (pCameraObject == _pScene->mpMainCamera)
				continue;

			RenderInstancing(pCameraObject->GetCamera(), pCameraObject->GetCamera()->GetDeferredObjects());
		}
	}

	void RenderManager::RenderLight(Scene* _pScene)
	{
		gpEngine->GetMultiRenderTarget(MultiRenderTargetType::Light)->OMSetRenderTarget();
		for (GameObject* pLightObject : _pScene->mLightObjects)
		{
			pLightObject->GetLight()->Render(_pScene->mpMainCamera->GetCamera());
		}
	}

	void RenderManager::RenderFinal(Scene* _pScene)
	{
		gpEngine->GetMultiRenderTarget(MultiRenderTargetType::SwapChain)->OMSetRenderTarget(1);

		GET_SINGLE(Resources)->Get<Material>(L"Final")->PushGraphicData();
		GET_SINGLE(Resources)->LoadRectMesh()->Render();
	}

	void RenderManager::PostProcessing(Scene* _pScene)
	{
		_pScene->mImageFilters.clear();
		Vec2 resolution = gpEngine->GetResolution();
		UINT width = static_cast<UINT>(resolution.x);
		UINT height = static_cast<UINT>(resolution.y);

		shared_ptr<ImageFilter> pCopyFilter = make_shared<ImageFilter>(GET_SINGLE(Resources)->Get<Material>(L"Copy")->Clone(), width, height);
		pCopyFilter->SetSRV(0, GET_SINGLE(Resources)->Get<Texture>(L"SwapChainTarget_0"));
		_pScene->mImageFilters.push_back(pCopyFilter);

		shared_ptr<ImageFilter> pDownSamplingFilter = make_shared<ImageFilter>(GET_SINGLE(Resources)->Get<Material>(L"Sampling")->Clone(), width, height);
		pDownSamplingFilter->SetSRV(0, GET_SINGLE(Resources)->Get<Texture>(L"SwapChainTarget_0"));
		_pScene->mImageFilters.push_back(pDownSamplingFilter);

		shared_ptr<Material> pBlurXMaterial = GET_SINGLE(Resources)->Get<Material>(L"BlurX")->Clone();
		pBlurXMaterial->SetTexture(0, _pScene->mImageFilters.back()->GetTexture());
		shared_ptr<BlurFilter> pBlurXFilter = make_shared<BlurFilter>(pBlurXMaterial, width / 8, height / 8);
		_pScene->mImageFilters.push_back(pBlurXFilter);

		shared_ptr<CombineFilter> pCombineFilter =
			make_shared<CombineFilter>(GET_SINGLE(Resources)->Get<Material>(L"Combine")->Clone(), width, height);
		pCombineFilter->SetSRV(0, pCopyFilter->GetTexture());
		pCombineFilter->SetSRV(1, _pScene->mImageFilters.back()->GetTexture());
		_pScene->mImageFilters.push_back(pCombineFilter);

		for (size_t i = 0; i < _pScene->mImageFilters.size(); ++i)
		{
			_pScene->mImageFilters[i]->Render();
		}
	}

	void RenderManager::PushLightData(Scene* _pScene)
	{
		LightParams lightParams = {};

		for (GameObject* pLightObject : _pScene->mLightObjects)
		{
			const LightInfo& lightInfo = pLightObject->GetLight()->GetLightInfo();

			pLightObject->GetLight()->SetLightIndex(lightParams.lightCount);

			lightParams.lights[lightParams.lightCount] = lightInfo;
			lightParams.lightCount++;
		}

		CONST_BUFFER(ConstantBufferType::Light)->PushData(&lightParams, sizeof(lightParams));
		CONST_BUFFER(ConstantBufferType::Light)->Mapping();
	}

	void RenderManager::AddParam(UINT64 _instanceID, InstancingParams& _params)
	{
		if (mBuffers.find(_instanceID) == mBuffers.end())
		{
			mBuffers[_instanceID] = new InstancingBuffer;
			mBuffers[_instanceID]->Initialize(sizeof(InstancingParams));
		}

		mBuffers[_instanceID]->AddData(_params);
	}
	void RenderManager::RenderInstancing(Camera* _pCamera, const std::vector<GameObject*> _gameObjects)
	{
		std::map<UINT64, std::vector<GameObject*>> tempMap;

		for (GameObject* pGameObject : _gameObjects)
		{
			//pGameObject->GetMeshRenderer()->Render(_pCamera);
			const UINT64 instanceID = pGameObject->GetMeshRenderer()->GetInstanceID();
			tempMap[instanceID].push_back(pGameObject);
		}

		for (auto& pair : tempMap)
		{
			const std::vector<GameObject*>& gameObjects = pair.second;

			if (gameObjects.size() == 1)
			{
				gameObjects[0]->GetMeshRenderer()->GetMaterial()->SetIntAllSubset(0, 0);
				gameObjects[0]->GetMeshRenderer()->Render(_pCamera);
			}

			else
			{
				const UINT64 instanceId = pair.first;

				for (GameObject* pGameObject : gameObjects)
				{
					InstancingParams params;
					params.matWorld = pGameObject->GetTransform()->GetWorldMatrix();
					params.matWV = params.matWorld * _pCamera->GetViewMatrix();
					params.matWVP = params.matWorld * _pCamera->GetViewMatrix() * _pCamera->GetProjectionMatrix();

					AddParam(instanceId, params);
				}

				InstancingBuffer* pBuffer = mBuffers[instanceId];
				gameObjects[0]->GetMeshRenderer()->GetMaterial()->SetIntAllSubset(0, 1);
				gameObjects[0]->GetMeshRenderer()->Render(_pCamera, pBuffer);
			}
		}
	}
}

