#include "pch.h"
#include "Shader.h"
#include "Engine.h"

namespace hm
{
	Shader::Shader()
		: Object(ObjectType::Shader)
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
				dsd.DepthEnable = TRUE;
				dsd.DepthFunc = D3D11_COMPARISON_LESS;
				dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
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
			}

			hr = DEVICE->CreateRasterizerState(&rd, mpRasterizerState.GetAddressOf());
			AssertEx(SUCCEEDED(hr), L"CreateRasterizerState Failed");
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
			}
			
			hr = DEVICE->CreateBlendState(&bs, mpBlendState.GetAddressOf());
			AssertEx(SUCCEEDED(hr), L"CreateBlendState Failed");
		}
#pragma endregion

	}
	void Shader::Update()
	{
		if (ShaderType::Compute == mShaderInfo.eShaderType)
		{
			CONTEXT->CSSetSamplers(0, 1, mpLinearSamplerState.GetAddressOf());
			CONTEXT->CSSetSamplers(1, 1, mpPointSamplerState.GetAddressOf());
			CONTEXT->CSSetShader(mpComputeShader.Get(), nullptr, 0);
		}

		else
		{
			CONTEXT->VSSetSamplers(0, 1, mpLinearSamplerState.GetAddressOf());
			CONTEXT->PSSetSamplers(0, 1, mpLinearSamplerState.GetAddressOf());
			CONTEXT->GSSetSamplers(0, 1, mpLinearSamplerState.GetAddressOf());

			CONTEXT->VSSetSamplers(1, 1, mpPointSamplerState.GetAddressOf());
			CONTEXT->PSSetSamplers(1, 1, mpPointSamplerState.GetAddressOf());
			CONTEXT->GSSetSamplers(1, 1, mpPointSamplerState.GetAddressOf());

			CONTEXT->VSSetShader(mpVertexShader.Get(), nullptr, 0);
			CONTEXT->PSSetShader(mpPixelShader.Get(), nullptr, 0);
			CONTEXT->GSSetShader(mpGeometryShader.Get(), nullptr, 0);
		}

		CONTEXT->IASetPrimitiveTopology(mShaderInfo.eTopology);
		CONTEXT->IASetInputLayout(mpInputLayout.Get());
		CONTEXT->RSSetState(mpRasterizerState.Get());

		CONTEXT->OMSetDepthStencilState(mpDepthStencilState.Get(), 0);
		CONTEXT->OMSetBlendState(mpBlendState.Get(), nullptr, 0xffffffff);
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
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		//samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;

		HRESULT hr = DEVICE->CreateSamplerState(&samplerDesc, mpLinearSamplerState.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"Shader::CreateSampler() - Create Linear Sampler Failed");

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
		hr = DEVICE->CreateSamplerState(&samplerDesc, mpPointSamplerState.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"Shader::CreateSampler() - Create Point Sampler Failed");
	}
}