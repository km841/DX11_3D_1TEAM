#include "pch.h"
#include "Mirror.h"
#include "GameObject.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Engine.h"
#include "Animator.h"
#include "InstancingBuffer.h"

namespace hm
{
	bool Mirror::sbIsInit = false;
	ComPtr<ID3D11RasterizerState> Mirror::spSolidRS;
	ComPtr<ID3D11RasterizerState> Mirror::spSolidCCWRS;

	ComPtr<ID3D11DepthStencilState> Mirror::spDrawDSS;
	ComPtr<ID3D11DepthStencilState> Mirror::spMaskDSS;
	ComPtr<ID3D11DepthStencilState> Mirror::spDrawMaskedDSS;
	ComPtr<ID3D11BlendState> Mirror::spMirrorBS;

	Mirror::Mirror()
		: Component(ComponentType::Mirror)
	{
	}

	Mirror::~Mirror()
	{
		for (auto& pair : mBuffers)
		{
			InstancingBuffer* buffer = pair.second;
			SAFE_DELETE(buffer);
		}
	}

	void Mirror::Initialize()
	{
		if (false == sbIsInit)
			InitRenderState();

		CreateReflectPlane();
	}

	void Mirror::Update()
	{

	}

	void Mirror::FinalUpdate()
	{

	}

	void Mirror::Render()
	{

	}

	Component* Mirror::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new Mirror);
	}

	void Mirror::CreateReflectPlane()
	{
		Vec3 pos = GetTransform()->GetPosition();
		mReflectPlane = Plane(pos, Vec3(0.f, 1.f, 0.f));
		mReflectMatrix = Matrix::CreateReflection(mReflectPlane);
	}
	void Mirror::ClearInstancingBuffer()
	{
		for (auto& pair : mBuffers)
		{
			InstancingBuffer* buffer = pair.second;
			buffer->ClearData();
		}
	}
	void Mirror::InitRenderState()
	{
		sbIsInit = true;
		D3D11_DEPTH_STENCIL_DESC dsDesc;
		ZeroMemory(&dsDesc, sizeof(dsDesc));
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
		dsDesc.StencilEnable = false; // Stencil 불필요
		dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		// 앞면에 대해서 어떻게 작동할지 설정
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		// 뒷면에 대해 어떻게 작동할지 설정 (뒷면도 그릴 경우)
		dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		HRESULT hr = DEVICE->CreateDepthStencilState(&dsDesc, spDrawDSS.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"RenderManager::MirrorInit() - 초기화 실패");

		// Stencil에 1로 표기해주는 DSS
		dsDesc.DepthEnable = true; // 이미 그려진 물체 유지
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
		dsDesc.StencilEnable = true;    // Stencil 필수
		dsDesc.StencilReadMask = 0xFF;  // 모든 비트 다 사용
		dsDesc.StencilWriteMask = 0xFF; // 모든 비트 다 사용
		// 앞면에 대해서 어떻게 작동할지 설정
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		hr = DEVICE->CreateDepthStencilState(&dsDesc, spMaskDSS.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"RenderManager::MirrorInit() - 초기화 실패");
		// Stencil에 1로 표기된 경우에"만" 그리는 DSS
		// DepthBuffer는 초기화된 상태로 가정
		// D3D11_COMPARISON_EQUAL 이미 1로 표기된 경우에만 그리기
		// OMSetDepthStencilState(..., 1); <- 여기의 1
		dsDesc.DepthEnable = true;   // 거울 속을 다시 그릴때 필요
		dsDesc.StencilEnable = true; // Stencil 사용
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL; // <- 주의
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;

		hr = DEVICE->CreateDepthStencilState(&dsDesc, spDrawMaskedDSS.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"RenderManager::MirrorInit() - 초기화 실패");

		D3D11_RASTERIZER_DESC rastDesc;
		ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
		rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rastDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		rastDesc.FrontCounterClockwise = false;
		rastDesc.DepthClipEnable = true;
		rastDesc.MultisampleEnable = false;

		hr = DEVICE->CreateRasterizerState(&rastDesc, spSolidRS.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"RenderManager::MirrorInit() - 초기화 실패");

		// 거울에 반사되면 삼각형의 Winding이 바뀌기 때문에 CCW로 그려야함
		rastDesc.FrontCounterClockwise = true;
		hr = DEVICE->CreateRasterizerState(&rastDesc, spSolidCCWRS.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"RenderManager::MirrorInit() - 초기화 실패");

		D3D11_BLEND_DESC mirrorBlendDesc;
		ZeroMemory(&mirrorBlendDesc, sizeof(mirrorBlendDesc));
		mirrorBlendDesc.AlphaToCoverageEnable = true; // MSAA
		mirrorBlendDesc.IndependentBlendEnable = false;
		// 개별 RenderTarget에 대해서 설정 (최대 8개)
		mirrorBlendDesc.RenderTarget[0].BlendEnable = true;
		mirrorBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_BLEND_FACTOR;
		mirrorBlendDesc.RenderTarget[0].DestBlend =
			D3D11_BLEND_INV_BLEND_FACTOR;
		mirrorBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		mirrorBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		mirrorBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		mirrorBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		// 필요하면 RGBA 각각에 대해서도 조절 가능
		mirrorBlendDesc.RenderTarget[0].RenderTargetWriteMask =
			D3D11_COLOR_WRITE_ENABLE_ALL;

		hr = DEVICE->CreateBlendState(&mirrorBlendDesc, spMirrorBS.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"RenderManager::MirrorInit() - 초기화 실패");
	}
	void Mirror::AddParam(UINT64 _instanceID, InstancingParams& _params)
	{
		if (mBuffers.find(_instanceID) == mBuffers.end())
		{
			mBuffers[_instanceID] = new InstancingBuffer;
			mBuffers[_instanceID]->Initialize(sizeof(InstancingParams));
		}

		mBuffers[_instanceID]->AddData(_params);
	}
	void Mirror::RenderMasking(Camera* _pCamera)
	{
		CONTEXT->OMSetDepthStencilState(spMaskDSS.Get(), 1);
		CONTEXT->RSSetState(spSolidRS.Get());

		GetTransform()->PushData(_pCamera);
		CONST_BUFFER(ConstantBufferType::Transform)->Mapping();
		shared_ptr<Mesh> pMesh = GetMeshRenderer()->GetMesh();
		shared_ptr<Material> pMaterial = GetMeshRenderer()->GetMaterial();
		shared_ptr<Shader> pShader = pMaterial->GetShader();

		pShader = GET_SINGLE(Resources)->Get<Shader>(L"Alpha");
		pShader->UpdateShaderAndSampler();
		pShader->UpdateInputLayout();
		pShader->UpdateTopology();

		pMaterial->PushGraphicDataExceptForShader();
		pMesh->Render();
	}
	void Mirror::RenderReflect(Camera* _pCamera)
	{
		gpEngine->GetMultiRenderTarget(MultiRenderTargetType::ScreenEffect)->ClearDepthView();

		ReflectParams params = {};
		params.reflectMatrix = mReflectMatrix;
		params.reflectRVPMatrix = params.reflectMatrix * _pCamera->GetViewMatrix() * _pCamera->GetProjectionMatrix();
		params.use = 1;
		CONST_BUFFER(ConstantBufferType::Reflect)->PushData(&params, sizeof(ReflectParams));
		CONST_BUFFER(ConstantBufferType::Reflect)->Mapping();

		ClearInstancingBuffer();
		auto reflectObjects = _pCamera->GetReflectObject();
		RenderInstancing(_pCamera, reflectObjects);

		params.reflectMatrix = Matrix::Identity;
		params.reflectRVPMatrix = Matrix::Identity;
		params.use = 0;
		CONST_BUFFER(ConstantBufferType::Reflect)->PushData(&params, sizeof(ReflectParams));
		CONST_BUFFER(ConstantBufferType::Reflect)->Mapping();
	}
	void Mirror::RenderInstancing(Camera* _pCamera, const std::vector<GameObject*> _gameObjects)
	{
		std::map<UINT64, std::vector<GameObject*>> tempMap;

		for (GameObject* pGameObject : _gameObjects)
		{
			UINT32 forwardMaterialID = GET_SINGLE(Resources)->Get<Material>(L"Forward")->GetID();
			UINT32 meshID = pGameObject->GetMeshRenderer()->GetMesh()->GetID();
			InstanceID id = {};
			id.materialID = forwardMaterialID;
			id.meshID = meshID;
			const UINT64 instanceID = id.id;
			tempMap[instanceID].push_back(pGameObject);
		}

		for (auto& pair : tempMap)
		{
			const std::vector<GameObject*>& gameObjects = pair.second;

			if (gameObjects.size() == 1)
			{
				gameObjects[0]->GetTransform()->PushData(_pCamera);
				CONST_BUFFER(ConstantBufferType::Transform)->Mapping();

				shared_ptr<Mesh> pObjectMesh = gameObjects[0]->GetMeshRenderer()->GetMesh();
				shared_ptr<Material> pObjectMaterial = gameObjects[0]->GetMeshRenderer()->GetMaterial();
				pObjectMaterial->SetIntAllSubset(0, 0);
				if (gameObjects[0]->GetAnimator())
				{
					gameObjects[0]->GetAnimator()->PushData();
					pObjectMaterial->SetIntAllSubset(1, 1);
				}

				UINT32 meshCount = pObjectMesh->GetMeshContainerCount();

				for (UINT32 i = 0; i < meshCount; ++i)
				{
					pObjectMaterial->PushGraphicDataExceptForShader(i);
					CONST_BUFFER(ConstantBufferType::Material)->Mapping();
					GET_SINGLE(Resources)->Get<Shader>(L"Forward")->UpdateShaderAndSampler();
					GET_SINGLE(Resources)->Get<Shader>(L"Forward")->UpdateTopology();
					GET_SINGLE(Resources)->Get<Shader>(L"Forward")->UpdateInputLayout();
					CONTEXT->OMSetDepthStencilState(spDrawMaskedDSS.Get(), 1);

					const float t = 0.05f;
					const float blendColor[] = { t, t, t, 1.0f };
					CONTEXT->OMSetBlendState(spMirrorBS.Get(), blendColor, 0xffffffff);
					CONTEXT->RSSetState(spSolidCCWRS.Get());
					pObjectMesh->Render(i);
				}
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

				gameObjects[0]->GetTransform()->PushData(_pCamera);
				CONST_BUFFER(ConstantBufferType::Transform)->Mapping();

				shared_ptr<Mesh> pObjectMesh = gameObjects[0]->GetMeshRenderer()->GetMesh();
				shared_ptr<Material> pObjectMaterial = gameObjects[0]->GetMeshRenderer()->GetMaterial();

				if (gameObjects[0]->GetAnimator())
				{
					gameObjects[0]->GetAnimator()->PushData();
					pObjectMaterial->SetIntAllSubset(1, 1);
				}

				pObjectMaterial->SetIntAllSubset(0, 1);
				UINT32 meshCount = pObjectMesh->GetMeshContainerCount();

				for (UINT32 i = 0; i < meshCount; ++i)
				{
					pObjectMaterial->PushGraphicDataExceptForShader(i);
					CONST_BUFFER(ConstantBufferType::Material)->Mapping();
					GET_SINGLE(Resources)->Get<Shader>(L"Forward")->UpdateShaderAndSampler();
					GET_SINGLE(Resources)->Get<Shader>(L"Forward")->UpdateTopology();
					GET_SINGLE(Resources)->Get<Shader>(L"Forward")->UpdateInputLayout();
					CONTEXT->OMSetDepthStencilState(spDrawMaskedDSS.Get(), 1);

					const float t = 0.05f;
					const float blendColor[] = { t, t, t, 1.0f };
					CONTEXT->OMSetBlendState(spMirrorBS.Get(), blendColor, 0xffffffff);
					CONTEXT->RSSetState(spSolidCCWRS.Get());
					pBuffer->PushData();
					pObjectMesh->RenderInstancing(pBuffer, i);
				}
			}
		}
	}
	void Mirror::RenderAlbedo(Camera* _pCamera)
	{
		shared_ptr<Mesh> pMesh = GetMeshRenderer()->GetMesh();
		shared_ptr<Material> pMaterial = GetMeshRenderer()->GetMaterial();

		const float t = 0.7f;
		const float blendColor[] = { t, t, t, 1.0f };
		CONTEXT->OMSetBlendState(spMirrorBS.Get(), blendColor, 0xffffffff);
		CONTEXT->RSSetState(spSolidRS.Get());

		GetTransform()->PushData(_pCamera);
		CONST_BUFFER(ConstantBufferType::Transform)->Mapping();

		pMaterial->PushGraphicDataExceptForShader();
		shared_ptr<Shader> pShader = GET_SINGLE(Resources)->Get<Shader>(L"Mirror");

		pShader->UpdateShaderAndSampler();
		pShader->UpdateInputLayout();
		pShader->UpdateTopology();
		pMesh->Render();


	}
}

