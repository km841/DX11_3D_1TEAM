#include "pch.h"
#include "Shader.h"
#include "Engine.h"

namespace hm
{
	Shader::Shader()
		: Object(ObjectType::Shader)
		, meSamplerType(SamplerType::Wrap)
	{
	}
	Shader::~Shader()
	{
	}
	void Shader::Load(const wstring& _path)
	{
	}
	void Shader::CreateGraphicsShader(const wstring& _path, ShaderInfo _shaderInfo, ShaderArg _shaderArg)
	{
		mShaderInfo = _shaderInfo;

		CreateVertexShader(_path, _shaderArg.vsFuncName, "vs_5_0");
		CreatePixelShader(_path, _shaderArg.psFuncName, "ps_5_0");

		if (false == _shaderArg.gsFuncName.empty())
			CreateGeometryShader(_path, _shaderArg.gsFuncName, "gs_5_0");

		CreateSampler();

		D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "INDICES", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 60, D3D11_INPUT_PER_VERTEX_DATA, 0},

			{ "W", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0,  D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{ "W", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{ "W", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{ "W", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{ "WV", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{ "WV", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 80, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{ "WV", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 96, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{ "WV", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 112, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{ "WVP", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 128, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{ "WVP", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 144, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{ "WVP", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 160, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{ "WVP", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 176, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		};

		HRESULT hr = DEVICE->CreateInputLayout(inputLayoutDesc, ARRAYSIZE(inputLayoutDesc), mpVSBlob->GetBufferPointer(), mpVSBlob->GetBufferSize(), &mpInputLayout);
		AssertEx(SUCCEEDED(hr), L"Shader::CreateGraphicsShader() - CreateInputLayout Failed");
#pragma region DepthStencilState
		{
			D3D11_DEPTH_STENCIL_DESC dsd = {};
			switch (_shaderInfo.eDepthStencilType)
			{
			case DepthStencilType::Less:
				dsd.DepthEnable = true;
				dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				dsd.DepthFunc = D3D11_COMPARISON_LESS;
				dsd.StencilEnable = false; // Stencil 불필요
				dsd.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
				dsd.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
				// 앞면에 대해서 어떻게 작동할지 설정
				dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
				dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
				// 뒷면에 대해 어떻게 작동할지 설정 (뒷면도 그릴 경우)
				dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
				dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
				dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
				break;

			case DepthStencilType::LessEqual:
				dsd.DepthEnable = TRUE;
				dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
				dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
				break;

			case DepthStencilType::Greater:
				dsd.DepthEnable = TRUE;
				dsd.DepthFunc = D3D11_COMPARISON_GREATER;
				dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
				break;

			case DepthStencilType::GreaterEqual:
				dsd.DepthEnable = TRUE;
				dsd.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
				dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
				break;

			case DepthStencilType::LessNoWrite:
				dsd.DepthEnable = TRUE;
				dsd.DepthFunc = D3D11_COMPARISON_LESS;
				dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
				break;

			case DepthStencilType::NoDepthTest:
				dsd.DepthEnable = FALSE;
				dsd.DepthFunc = D3D11_COMPARISON_LESS;
				dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
				break;

			case DepthStencilType::NoDepthTestNoWrite:
				dsd.DepthEnable = FALSE;
				dsd.DepthFunc = D3D11_COMPARISON_LESS;
				dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
				break;

			case DepthStencilType::MaskStencil:
				// Stencil에 1로 표기해주는 DSS
				dsd.DepthEnable = true; // 이미 그려진 물체 유지
				dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
				dsd.DepthFunc = D3D11_COMPARISON_LESS;
				dsd.StencilEnable = true;    // Stencil 필수
				dsd.StencilReadMask = 0xFF;  // 모든 비트 다 사용
				dsd.StencilWriteMask = 0xFF; // 모든 비트 다 사용
				// 앞면에 대해서 어떻게 작동할지 설정
				dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
				dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
				dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
				// 뒷면에 대해 어떻게 작동할지 설정 (뒷면도 그릴 경우)
				dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
				dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
				dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
				break;

			case DepthStencilType::LessEqualStencil:
				dsd.DepthEnable = true;   // 거울 속을 다시 그릴때 필요
				dsd.StencilEnable = true; // Stencil 사용
				dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL; // <- 주의
				dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
				dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				dsd.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;
				// 뒷면에 대해 어떻게 작동할지 설정 (뒷면도 그릴 경우)
				dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
				dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
				dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
				break;
			}

			hr = DEVICE->CreateDepthStencilState(&dsd, mpDepthStencilState.GetAddressOf());
			AssertEx(SUCCEEDED(hr), L"CreateDepthStencilState Failed");
		}
#pragma endregion

#pragma region RasterizerState
		{
			D3D11_RASTERIZER_DESC rd = {};
			rd.MultisampleEnable = true;
			rd.AntialiasedLineEnable = true;

			switch (_shaderInfo.eRasterizerType)
			{
			case RasterizerType::CullBack:
				rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
				rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
				break;

			case RasterizerType::CullFront:
				rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
				rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
				break;

			case RasterizerType::CullNone:
				rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
				rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
				break;

			case RasterizerType::WireFrame:
				rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
				rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
				break;

			case RasterizerType::CullBackCCW:
				rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
				rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
				rd.FrontCounterClockwise = true;
				break;

			case RasterizerType::CullFrontCCW:
				rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
				rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
				rd.FrontCounterClockwise = true;
				break;

			}

			hr = DEVICE->CreateRasterizerState(&rd, mpRasterizerState.GetAddressOf());
			AssertEx(SUCCEEDED(hr), L"Shader::CreateRasterizerState() - 생성 실패");
		}
#pragma endregion

#pragma region BlendState
		{
			if (BlendType::Default == _shaderInfo.eBlendType)
				return;

			D3D11_BLEND_DESC bs = {};
			switch (_shaderInfo.eBlendType)
			{

			case BlendType::AlphaBlend:
				bs.AlphaToCoverageEnable = FALSE;
				bs.IndependentBlendEnable = FALSE;
				bs.RenderTarget[0].BlendEnable = TRUE;
				bs.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
				bs.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
				bs.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
				bs.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
				bs.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
				bs.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
				bs.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
				break;

			case BlendType::OneToOneBlend:
				bs.AlphaToCoverageEnable = false;
				bs.IndependentBlendEnable = false;
				bs.RenderTarget[0].BlendEnable = true;
				bs.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
				bs.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
				bs.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
				bs.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
				bs.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
				bs.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
				bs.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
				break;

			case BlendType::CustumBlend:
				bs.AlphaToCoverageEnable = false; // MSAA
				bs.IndependentBlendEnable = false;
				// 개별 RenderTarget에 대해서 설정 (최대 8개)
				bs.RenderTarget[0].BlendEnable = true;
				bs.RenderTarget[0].SrcBlend = D3D11_BLEND_BLEND_FACTOR;
				bs.RenderTarget[0].DestBlend = D3D11_BLEND_INV_BLEND_FACTOR;
				bs.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

				bs.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
				bs.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
				bs.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

				// 필요하면 RGBA 각각에 대해서도 조절 가능
				bs.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
				break;
			}
			
			hr = DEVICE->CreateBlendState(&bs, mpBlendState.GetAddressOf());
			AssertEx(SUCCEEDED(hr), L"Shader::CreateBlendState() - Failed");
		}
#pragma endregion

	}
	void Shader::Update()
	{
		UpdateShaderAndSampler();
		UpdateTopology();
		UpdateInputLayout();
		UpdateRenderState();
	}
	void Shader::UpdateShaderAndSampler()
	{
		if (ShaderType::Compute == mShaderInfo.eShaderType)
		{
			switch (meSamplerType)
			{
			case hm::SamplerType::Wrap:
				CONTEXT->CSSetSamplers(0, 1, mpLinearWrapSamplerState.GetAddressOf());
				CONTEXT->CSSetSamplers(1, 1, mpPointWrapSamplerState.GetAddressOf());
				break;
			case hm::SamplerType::Clamp:
				CONTEXT->CSSetSamplers(0, 1, mpLinearClampSamplerState.GetAddressOf());
				CONTEXT->CSSetSamplers(1, 1, mpPointClampSamplerState.GetAddressOf());
				break;
			}
			CONTEXT->CSSetShader(mpComputeShader.Get(), nullptr, 0);
		}

		else
		{
			switch (meSamplerType)
			{
			case hm::SamplerType::Wrap:
				CONTEXT->VSSetSamplers(0, 1, mpLinearWrapSamplerState.GetAddressOf());
				CONTEXT->PSSetSamplers(0, 1, mpLinearWrapSamplerState.GetAddressOf());
				CONTEXT->GSSetSamplers(0, 1, mpLinearWrapSamplerState.GetAddressOf());
				CONTEXT->VSSetSamplers(1, 1, mpPointWrapSamplerState.GetAddressOf());
				CONTEXT->PSSetSamplers(1, 1, mpPointWrapSamplerState.GetAddressOf());
				CONTEXT->GSSetSamplers(1, 1, mpPointWrapSamplerState.GetAddressOf());
				break;
			case hm::SamplerType::Clamp:
				CONTEXT->VSSetSamplers(0, 1, mpLinearClampSamplerState.GetAddressOf());
				CONTEXT->PSSetSamplers(0, 1, mpLinearClampSamplerState.GetAddressOf());
				CONTEXT->GSSetSamplers(0, 1, mpLinearClampSamplerState.GetAddressOf());
				CONTEXT->VSSetSamplers(1, 1, mpPointClampSamplerState.GetAddressOf());
				CONTEXT->PSSetSamplers(1, 1, mpPointClampSamplerState.GetAddressOf());
				CONTEXT->GSSetSamplers(1, 1, mpPointClampSamplerState.GetAddressOf());
				break;
			case hm::SamplerType::WrapClamp:
				CONTEXT->VSSetSamplers(0, 1, mpLinearWrapSamplerState.GetAddressOf());
				CONTEXT->PSSetSamplers(0, 1, mpLinearWrapSamplerState.GetAddressOf());
				CONTEXT->GSSetSamplers(0, 1, mpLinearWrapSamplerState.GetAddressOf());
				CONTEXT->VSSetSamplers(1, 1, mpLinearClampSamplerState.GetAddressOf());
				CONTEXT->PSSetSamplers(1, 1, mpLinearClampSamplerState.GetAddressOf());
				CONTEXT->GSSetSamplers(1, 1, mpLinearClampSamplerState.GetAddressOf());
				break;
			}

			CONTEXT->VSSetSamplers(2, 1, mpShadowSamplerState.GetAddressOf());
			CONTEXT->PSSetSamplers(2, 1, mpShadowSamplerState.GetAddressOf());
			CONTEXT->GSSetSamplers(2, 1, mpShadowSamplerState.GetAddressOf());

			CONTEXT->VSSetShader(mpVertexShader.Get(), nullptr, 0);
			CONTEXT->PSSetShader(mpPixelShader.Get(), nullptr, 0);
			CONTEXT->GSSetShader(mpGeometryShader.Get(), nullptr, 0);
		}
	}
	void Shader::UpdateTopology()
	{
		CONTEXT->IASetPrimitiveTopology(mShaderInfo.eTopology);
	}
	void Shader::UpdateInputLayout()
	{
		CONTEXT->IASetInputLayout(mpInputLayout.Get());
	}
	void Shader::UpdateRenderState()
	{
		CONTEXT->RSSetState(mpRasterizerState.Get());

		CONTEXT->OMSetDepthStencilState(mpDepthStencilState.Get(), 1);

		bool bIsMirror = ShaderType::Masking == mShaderInfo.eShaderType;
		const float blendColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		CONTEXT->OMSetBlendState(mpBlendState.Get(), bIsMirror ? blendColor : nullptr, 0xffffffff);
	}
	void Shader::CreateComputeShader(const wstring& _path, const string& _name, const string& _version)
	{
		mShaderInfo.eShaderType = ShaderType::Compute;
		CreateSampler();
		CreateShader(_path, _name, _version, mpCSBlob);
		HRESULT hr = DEVICE->CreateComputeShader(mpCSBlob->GetBufferPointer(), mpCSBlob->GetBufferSize(), nullptr, &mpComputeShader);
		assert(SUCCEEDED(hr));
	}
	void Shader::CreateVertexShader(const wstring& _path, const string& _name, const string& _version)
	{
		CreateShader(_path, _name, _version, mpVSBlob);
		HRESULT hr = DEVICE->CreateVertexShader(mpVSBlob->GetBufferPointer(), mpVSBlob->GetBufferSize(), nullptr, &mpVertexShader);
		AssertEx(SUCCEEDED(hr), L"Shader::CreateVertexShader() - CreateVertexShader Failed");
	}
	void Shader::CreatePixelShader(const wstring& _path, const string& _name, const string& _version)
	{
		CreateShader(_path, _name, _version, mpPSBlob);
		HRESULT hr = DEVICE->CreatePixelShader(mpPSBlob->GetBufferPointer(), mpPSBlob->GetBufferSize(), nullptr, &mpPixelShader);
		AssertEx(SUCCEEDED(hr), L"Shader::CreatePixelShader() - CreatePixelShader Failed");
	}
	void Shader::CreateGeometryShader(const wstring& _path, const string& _name, const string& _version)
	{
		CreateShader(_path, _name, _version, mpGSBlob);
		HRESULT hr = DEVICE->CreateGeometryShader(mpGSBlob->GetBufferPointer(), mpGSBlob->GetBufferSize(), nullptr, &mpGeometryShader);
		AssertEx(SUCCEEDED(hr), L"Shader::CreateGeometryShader() - CreateGeometryShader Failed");
	}
	void Shader::SetSamplerType(SamplerType _eSamplerType)
	{
		meSamplerType = _eSamplerType;
	}
	void Shader::SetBackfaceCulling(bool _bBackfaceCulling)
	{
		if (nullptr != mpRasterizerState)
		{
			mpRasterizerState->Release();
		}

		D3D11_RASTERIZER_DESC rd = {};
		rd.MultisampleEnable = true;
		rd.AntialiasedLineEnable = true;
		rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rd.CullMode = true == _bBackfaceCulling ? D3D11_CULL_MODE::D3D11_CULL_BACK : D3D11_CULL_MODE::D3D11_CULL_NONE;

		HRESULT hr = DEVICE->CreateRasterizerState(&rd, mpRasterizerState.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"Shader::SetBackfaceCulling() - CreateRasterizerState Failed");
	}

	void Shader::PushInputLayout()
	{
		CONTEXT->IASetInputLayout(mpInputLayout.Get());
	}

	void Shader::CreateShader(const wstring& _path, const string& _name, const string& _version, ComPtr<ID3DBlob>& _pBlob)
	{
		int compileFlag = 0;
#ifdef _DEBUG
		compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		HRESULT hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			_name.c_str(), _version.c_str(), compileFlag, 0, &_pBlob, &mpErrBlob);

		if (FAILED(hr))
		{
			const char* errorString = NULL;
			if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
				errorString = "Could not compile shader; file not found";
			else if (mpErrBlob) {
				errorString = (const char*)mpErrBlob->GetBufferPointer();
				mpErrBlob->Release();
			}
			AssertEx(NULL, L"Shader::CreateShader() - Shader Compiler Error");
		}
	}
	void Shader::CreateSampler()
	{
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		//samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;

		HRESULT hr = DEVICE->CreateSamplerState(&samplerDesc, mpLinearWrapSamplerState.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"Shader::CreateSampler() - Create Linear Sampler Failed");

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
		hr = DEVICE->CreateSamplerState(&samplerDesc, mpPointWrapSamplerState.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"Shader::CreateSampler() - Create Point Sampler Failed");

		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;

		hr = DEVICE->CreateSamplerState(&samplerDesc, mpPointClampSamplerState.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"Shader::CreateSampler() - Create Point Sampler Failed");

		hr = DEVICE->CreateSamplerState(&samplerDesc, mpLinearClampSamplerState.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"Shader::CreateSampler() - Create Linear Sampler Failed");


		// Shadow Sampler

		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.BorderColor[0] = 100.f;
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;

		hr = DEVICE->CreateSamplerState(&samplerDesc, mpShadowSamplerState.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"Shader::CreateSampler() - Create Shadow Sampler Failed");
	}
}