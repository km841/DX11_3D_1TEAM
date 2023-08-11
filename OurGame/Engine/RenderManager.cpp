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
		: mWidth(0)
		, mHeight(0)
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
		mWidth = gpEngine->GetWindowInfo().width;
		mHeight = gpEngine->GetWindowInfo().height;

		mpCopyFilter = make_shared<ImageFilter>(GET_SINGLE(Resources)->Get<Material>(L"Copy"), mWidth, mHeight);
		mpSamplingFilter = make_shared<ImageFilter>(GET_SINGLE(Resources)->Get<Material>(L"Sampling"), mWidth, mHeight);
		mpBlurYFilter = make_shared<BlurFilter>(GET_SINGLE(Resources)->Get<Material>(L"BlurY"), mWidth / 6, mHeight / 6);
		mpBlurXFilter = make_shared<BlurFilter>(GET_SINGLE(Resources)->Get<Material>(L"BlurX"), mWidth / 6, mHeight / 6);
		mpCombineFilter = make_shared<CombineFilter>(GET_SINGLE(Resources)->Get<Material>(L"Combine"), mWidth, mHeight);
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

		PostProcessing();
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

	void RenderManager::PostProcessing()
	{
		Bloom();
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

	void RenderManager::Blur()
	{
		shared_ptr<Texture> pBackTexture = nullptr;
		shared_ptr<Texture> pSwapChainTex = GET_SINGLE(Resources)->Get<Texture>(L"SwapChainTarget_0");

		mpCopyFilter->SetSRV(0, pSwapChainTex);
		mpCopyFilter->Render();

		mpSamplingFilter->SetSRV(0, pSwapChainTex);
		mpSamplingFilter->Render();

		mpBlurYFilter->SetSRV(0, mpSamplingFilter->GetTexture());
		mpBlurYFilter->Render();

		mpBlurXFilter->SetSRV(0, mpBlurYFilter->GetTexture());
		mpBlurXFilter->Render();
	}

	void RenderManager::Bloom()
	{
		Blur();

		mpCombineFilter->SetSRV(0, mpCopyFilter->GetTexture());
		mpCombineFilter->SetSRV(1, mpBlurXFilter->GetTexture());
		mpCombineFilter->Render();
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

