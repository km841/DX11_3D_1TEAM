#include "pch.h"
#include "Light.h"
#include "GameObject.h"
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"
#include "Resources.h"
#include "Camera.h"
#include "Engine.h"

namespace hm
{
	Light::Light()
		: Component(ComponentType::Light)
		, mLightIndex(-1)
		, mpShadowCamera(nullptr)
	{
		mpShadowCamera = new GameObject(LayerType::Unknown);
		Transform* pTransform = mpShadowCamera->AddComponent(new Transform);
		Camera* pCamera = mpShadowCamera->AddComponent(new Camera);
		pCamera->SetCullingMask(LayerType::Interface, true);

		mpStaticShadowMap = GET_SINGLE(Resources)->CreateTexture(
			std::to_wstring((UINT64)this) + L"S",
			DXGI_FORMAT_R32_FLOAT,
			D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
			4096, 4096);

		mpStaticDepthMap = GET_SINGLE(Resources)->CreateTexture(
			std::to_wstring((UINT64)this) + L"SD",
			DXGI_FORMAT_D32_FLOAT,
			D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL,
			4096, 4096);

		mpDynamicShadowMap = GET_SINGLE(Resources)->CreateTexture(
			std::to_wstring((UINT64)this) + L"D",
			DXGI_FORMAT_R32_FLOAT,
			D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
			4096, 4096);

		mpDynamicDepthMap = GET_SINGLE(Resources)->CreateTexture(
			std::to_wstring((UINT64)this) + L"DD",
			DXGI_FORMAT_D32_FLOAT,
			D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL,
			4096, 4096);
	}
	Light::~Light()
	{
		SAFE_DELETE(mpShadowCamera);
	}
	void Light::FinalUpdate()
	{
		if (nullptr != mpShadowCamera)
		{
			Vec3 camPos = GetTransform()->GetPosition();
			if (LightType::PointLight == static_cast<LightType>(mLightInfo.eLightType))
				camPos.y += 30.f;
			

			mpShadowCamera->GetTransform()->SetRotation(GetTransform()->GetRotation());
			mpShadowCamera->GetTransform()->SetPosition(camPos);
			mpShadowCamera->GetTransform()->SetScale(GetTransform()->GetScale());
			mpShadowCamera->FinalUpdate();
		}

		Vec3 worldPos = GetTransform()->GetPosition();
		mLightInfo.position = Vec4(worldPos.x, worldPos.y, worldPos.z, 1.f);

		Vec3 lookDir = mpShadowCamera->GetTransform()->GetLook();
		lookDir.Normalize();
		mLightInfo.direction = lookDir;

	}
	void Light::Render(Camera* _pCamera)
	{
		AssertEx(mLightIndex >= 0, L"Light::Render() - LightIndex가 지정되지 않음");
		GetTransform()->PushData(_pCamera);

		Matrix matVP = mpShadowCamera->GetCamera()->GetViewMatrix() * mpShadowCamera->GetCamera()->GetProjectionMatrix();
		mpMaterial->SetMatrix(0, matVP);

		if (LightType::DirectionalLight != static_cast<LightType>(mLightInfo.eLightType))
		{
			float scale = mLightInfo.range * 2.f;
			GetTransform()->SetScale(Vec3(scale, scale, scale));
		}
		
		mpMaterial->SetTexture(2, mpStaticShadowMap);
		mpMaterial->SetTexture(3, mpDynamicShadowMap);

		mpMaterial->SetInt(0, mLightIndex);
		mpMaterial->PushGraphicData();
		mpMesh->Render();
	}
	Component* Light::Clone(GameObject* _pGameObject)
	{
		Light* pLight = _pGameObject->AddComponent(new Light);
		pLight->mLightInfo = mLightInfo;
		pLight->mLightIndex = -1;
		pLight->mpMesh = mpMesh;
		pLight->mpMaterial = mpMaterial;

		return pLight;
	}
	void Light::RenderStaticShadow()
	{
		float clearColors[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		CONTEXT->ClearRenderTargetView(mpStaticShadowMap->GetRTV().Get(), clearColors);
		CONTEXT->ClearDepthStencilView(mpStaticDepthMap->GetDSV().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

		Vec3 texSize = mpStaticShadowMap->GetTexSize();
		D3D11_VIEWPORT vp = D3D11_VIEWPORT{ 0.f, 0.f, texSize.x, texSize.y, 0.f, 1.f };
		D3D11_RECT rect = D3D11_RECT{ 0, 0, static_cast<LONG>(texSize.x), static_cast<LONG>(texSize.y) };

		CONTEXT->RSSetViewports(1, &vp);
		CONTEXT->RSSetScissorRects(1, &rect);

		CONTEXT->OMSetRenderTargets(1, mpStaticShadowMap->GetRTV().GetAddressOf(), mpStaticDepthMap->GetDSV().Get());

		mpShadowCamera->GetCamera()->SortStaticShadowObject();
		mpShadowCamera->GetCamera()->RenderShadow();
	}
	void Light::RenderDynamicShadow()
	{
		float clearColors[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		CONTEXT->ClearRenderTargetView(mpDynamicShadowMap->GetRTV().Get(), clearColors);
		CONTEXT->ClearDepthStencilView(mpDynamicDepthMap->GetDSV().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

		Vec3 texSize = mpDynamicShadowMap->GetTexSize();
		D3D11_VIEWPORT vp = D3D11_VIEWPORT{ 0.f, 0.f, texSize.x, texSize.y, 0.f, 1.f };
		D3D11_RECT rect = D3D11_RECT{ 0, 0, static_cast<LONG>(texSize.x), static_cast<LONG>(texSize.y) };

		CONTEXT->RSSetViewports(1, &vp);
		CONTEXT->RSSetScissorRects(1, &rect);

		CONTEXT->OMSetRenderTargets(1, mpDynamicShadowMap->GetRTV().GetAddressOf(), mpDynamicDepthMap->GetDSV().Get());

		mpShadowCamera->GetCamera()->SortDynamicShadowObject();
		mpShadowCamera->GetCamera()->RenderShadow();
	}
	void Light::SetLightDirection(Vec3 _direction)
	{
		_direction.Normalize();
		mLightInfo.direction = _direction;

		GetTransform()->LookAt(_direction);
	}
	void Light::SetLightType(LightType _eLightType)
	{
		mLightInfo.eLightType = static_cast<int>(_eLightType);

		switch (_eLightType)
		{
		case LightType::DirectionalLight:
			mpMesh = GET_SINGLE(Resources)->LoadRectMesh();
			mpMaterial = GET_SINGLE(Resources)->Get<Material>(L"DirLight");
			break;
		case LightType::PointLight:
		case LightType::SpotLight:
			mpMesh = GET_SINGLE(Resources)->LoadSphereMesh();
			mpMaterial = GET_SINGLE(Resources)->Get<Material>(L"PointLight");
			break;
		}

		mpShadowCamera->GetCamera()->SetScale(1.f);
		mpShadowCamera->GetCamera()->SetFar(10000.f);
		mpShadowCamera->GetCamera()->SetWidth(4096.f);
		mpShadowCamera->GetCamera()->SetHeight(4096.f);
		//mpShadowCamera->GetCamera()->SetFov(XM_PI / 2.f);
	}

	void Light::SetShadowCamera(GameObject* _pShadowCamera)
	{
		mpShadowCamera = _pShadowCamera;
	}
}

