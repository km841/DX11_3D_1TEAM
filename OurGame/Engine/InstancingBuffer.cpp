#include "pch.h"
#include "InstancingBuffer.h"
#include "Engine.h"

namespace hm
{
	void InstancingBuffer::Initialize(UINT32 _bufferSize, UINT32 _maxCount)
	{
		mMaxCount = _maxCount;

		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = _bufferSize * mMaxCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;		
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, mpInstancingBuffer.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"InstancingBuffer::Initialize() - Buffer 생성 실패");
	}

	void InstancingBuffer::ClearData()
	{
		mData.clear();
	}

	void InstancingBuffer::AddData(InstancingParams& _params)
	{
		mData.push_back(_params);
	}

	void InstancingBuffer::PushData()
	{
		D3D11_MAPPED_SUBRESOURCE mappedSubResource = {};
		HRESULT hr = CONTEXT->Map(mpInstancingBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);
		AssertEx(SUCCEEDED(hr), L"InstancingBuffer::PushData() - 데이터를 집어넣는 과정에서 에러 발생");
		memcpy(mappedSubResource.pData, mData.data(), mData.size() * sizeof(InstancingParams));
		CONTEXT->Unmap(mpInstancingBuffer.Get(), 0);
	}
}

