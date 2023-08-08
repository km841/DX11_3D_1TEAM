#include "pch.h"
#include "ConstantBuffer.h"
#include "Engine.h"

namespace hm
{
	ConstantBuffer::ConstantBuffer()
		: meReg(RegisterCBV::End)
	{
	}

	ConstantBuffer::~ConstantBuffer()
	{
	}

	void ConstantBuffer::Create(RegisterCBV _eReg, int _size)
	{
		AssertEx(_eReg != RegisterCBV::End, L"CBV value is wrong");
		meReg = _eReg;
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = _size;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, mpBuffer.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"ConstantBuffer::Create() - ConstantBuffer 생성 실패");
	}

	void ConstantBuffer::Mapping()
	{
		CONTEXT->VSSetConstantBuffers(static_cast<UINT>(meReg), 1, mpBuffer.GetAddressOf());
		CONTEXT->PSSetConstantBuffers(static_cast<UINT>(meReg), 1, mpBuffer.GetAddressOf());
		CONTEXT->GSSetConstantBuffers(static_cast<UINT>(meReg), 1, mpBuffer.GetAddressOf());
		CONTEXT->CSSetConstantBuffers(static_cast<UINT>(meReg), 1, mpBuffer.GetAddressOf());
	}

	void ConstantBuffer::PushData(void* _pData, int _size)
	{
		D3D11_MAPPED_SUBRESOURCE mappedSubResource = {};
		HRESULT hr = CONTEXT->Map(mpBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);
		AssertEx(SUCCEEDED(hr), L"ConstantBuffer::PushData() - ConstantBuffer에 데이터를 집어넣는 과정에서 에러 발생");
		memcpy(mappedSubResource.pData, _pData, _size);
		CONTEXT->Unmap(mpBuffer.Get(), 0);
	}
}

