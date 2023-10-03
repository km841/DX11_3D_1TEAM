#include "pch.h"
#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"
#include "Engine.h"
#include "SceneManager.h"
#include "Scene.h"
#include "MeshRenderer.h"
#include "ParticleSystem.h"
#include "Effect.h"

namespace hm
{
	Camera::Camera()
		: Component(ComponentType::Camera)
		, meProjectionType(ProjectionType::Perspective)
		, mNear(1.f)
		, mFar(10000.f)
		, mFov(XM_PI/4.f)
		, mScale(1.f)
		, mCullingMask(0)
		, mWidth(0.f)
		, mHeight(0.f)
	{
		Vec2 resolution = gpEngine->GetResolution();
		mWidth = resolution.x;
		mHeight = resolution.y;
	}
	Camera::~Camera()
	{
	}
	Component* Camera::Clone(GameObject* _pGameObject)
	{
		Camera* pCamera = _pGameObject->AddComponent(new Camera);
		pCamera->meProjectionType = meProjectionType;
		pCamera->mCullingMask = mCullingMask;

		return pCamera;
	}
	void Camera::Update()
	{
	}
	void Camera::FinalUpdate()
	{
		Matrix matWorld = GetTransform()->GetWorldMatrix();
		Matrix matWorldInv = matWorld.Invert();
		mMatView = matWorldInv;

		if (ProjectionType::Perspective == meProjectionType)
		{
			mMatProjection = XMMatrixPerspectiveFovLH(mFov, mWidth / mHeight, mNear, mFar);
		}
		else
		{
			mMatProjection = XMMatrixOrthographicLH(mWidth / mScale, mHeight / mScale, mNear, mFar);
		}

		mFrustumCulling.FinalUpdate(this);
	}
	void Camera::SetCullingMask(LayerType _eLayerType, bool _bFlag)
	{
		if (_bFlag)
			mCullingMask |= 1 << static_cast<int>(_eLayerType);
		else
			mCullingMask &= ~(1 << static_cast<int>(_eLayerType));
	}
	void Camera::DisableAllCullingMask()
	{
		mCullingMask = 0;
	}
	void Camera::EnableAllCullingMask()
	{
		for (int i = 0; i < LAYER_TYPE_COUNT - 1; ++i)
		{
			mCullingMask |= 1 << i;
		}
	}
	void Camera::SortGameObject()
	{
		mForwardObjects.clear();
		mDeferredObjects.clear();
		mParticleObjects.clear();
		mEffectObjects.clear();
		mReflectObjects.clear();

		for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
		{
			if (mCullingMask & (1 << i))
				continue;

			const std::vector<GameObject*>& gameObjects =
				GET_SINGLE(SceneManager)->GetActiveScene()->GetGameObjects(static_cast<LayerType>(i));

			for (GameObject* pGameObject : gameObjects)
			{
				if (false == pGameObject->IsEnable())
					continue; 

				if (pGameObject->IsFrustumCheck())
				{
					if (false == mFrustumCulling.ContainsSphere(
						pGameObject->GetTransform()->GetWorldPosition(),
						pGameObject->GetTransform()->GetBoundingSphereRadius()))
						continue;
				}

				if (nullptr != pGameObject->GetMeshRenderer())
				{
					if (true == pGameObject->IsReflect())
						mReflectObjects.push_back(pGameObject);

					if (LayerType::Effect == pGameObject->GetLayerType())
						mEffectObjects.push_back(pGameObject);

					if (nullptr == pGameObject->GetMeshRenderer()->GetMaterial())
						continue;

					ShaderType eShaderType = pGameObject->GetMeshRenderer()->GetMaterial()->GetShader()->GetShaderType();

					switch (eShaderType)
					{
					case hm::ShaderType::Forward:
						mForwardObjects.push_back(pGameObject);
						break;
					case hm::ShaderType::Deferred:
						mDeferredObjects.push_back(pGameObject);
						break;
					default:
						AssertEx(false, L"잘못된 셰이더 타입");
						break;
					}
				}
				else
				{
					if (nullptr != pGameObject->GetParticleSystem())
						mParticleObjects.push_back(pGameObject);
				}
			}
		}
	}
	void Camera::SortStaticShadowObject()
	{
		mShadowObjects.clear();
		Scene* pActiveScene = GET_SINGLE(SceneManager)->GetActiveScene();

		for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
		{
			if (mCullingMask & 1 << i)
				continue;

			if (LayerType::Player == static_cast<LayerType>(i) ||
				LayerType::Monster == static_cast<LayerType>(i) ||
				LayerType::Npc == static_cast<LayerType>(i))
				continue;

			const auto& gameObjects = pActiveScene->GetGameObjects(static_cast<LayerType>(i));

			for (auto& pGameObject : gameObjects)
			{
				if (nullptr == pGameObject->GetMeshRenderer())
					continue;

				if (false == pGameObject->IsDrawShadow())
					continue;

				if (false == pGameObject->IsEnable())
					continue;

				mShadowObjects.push_back(pGameObject);
			}
		}
	}
	void Camera::SortDynamicShadowObject()
	{
		mShadowObjects.clear();
		Scene* pActiveScene = GET_SINGLE(SceneManager)->GetActiveScene();

		for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
		{
			if (mCullingMask & 1 << i)
				continue;

			if (LayerType::Player != static_cast<LayerType>(i) &&
				LayerType::Monster != static_cast<LayerType>(i) &&
				LayerType::Npc != static_cast<LayerType>(i))
				continue;

			const auto& gameObjects = pActiveScene->GetGameObjects(static_cast<LayerType>(i));

			for (auto& pGameObject : gameObjects)
			{
				if (nullptr == pGameObject->GetMeshRenderer())
					continue;

				if (false == pGameObject->IsDrawShadow())
					continue;

				if (false == pGameObject->IsEnable())
					continue;

				mShadowObjects.push_back(pGameObject);
			}
		}
	}
	void Camera::RenderForward()
	{
		for (GameObject* pGameObject : mForwardObjects)
		{

			pGameObject->GetMeshRenderer()->Render(this);
		}
	}
	void Camera::RenderDeferred()
	{
		for (GameObject* pGameObject : mDeferredObjects)
		{
			pGameObject->GetMeshRenderer()->Render(this);
		}
	}
	void Camera::RenderParticle()
	{
		for (GameObject* pGameObject : mParticleObjects)
		{
			pGameObject->GetParticleSystem()->Render(this);
		}
	}
	void Camera::RenderShadow()
	{
		size_t size = mShadowObjects.size();
		for (auto& pGameObject : mShadowObjects)
		{
			pGameObject->GetMeshRenderer()->RenderShadow(this);
		}
	}
	void Camera::RenderEffect()
	{
		for (GameObject* pGameObject : mEffectObjects)
		{
			Effect* pEffect = static_cast<Effect*>(pGameObject);
			pEffect->PushBloomData();
			pEffect->GetMeshRenderer()->RenderEffect(this);
		}
	}

	void Camera::RenderReflect(shared_ptr<Shader> _pShader)
	{
		for (GameObject* pGameObject : mReflectObjects)
		{
			pGameObject->GetMeshRenderer()->RenderExceptForShader(this, _pShader, true);
		}
	}


	bool Camera::ZSort(GameObject* _pFirst, GameObject* _pSecond)
	{
		Transform* pTrFirst = _pFirst->GetTransform();
		Transform* pTrSecond = _pSecond->GetTransform();

		if (nullptr == pTrFirst || nullptr == pTrSecond)
			return false;

		return pTrFirst->GetPosition().z > pTrSecond->GetPosition().z;
	}
}