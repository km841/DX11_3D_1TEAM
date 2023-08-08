#include "pch.h"
#include "StructuredBuffer.h"
#include "Engine.h"

namespace hm
{
    StructuredBuffer::StructuredBuffer()
        : mpWriteBuffer(nullptr)
        , mpReadBuffer(nullptr)
        , mSRVSlot(0)
        , mUAVSlot(0)
        , mppNullptr(nullptr)
        , mElementSize(0)
        , mElementCount(0)
    {
    }
    StructuredBuffer::~StructuredBuffer()
    {
    }
    void StructuredBuffer::Create(int _elementSize, int _elementCount, void* _pInitialData, bool _bCpuAccess)
    {
        mElementSize = _elementSize;
        mElementCount = _elementCount;

        CreateBuffer(_pInitialData);
        CreateView();

        if (_bCpuAccess)
            CreateRWBuffer();
    }
    void StructuredBuffer::SetData(void* _pData, int _elementCount)
    {
        if (mElementCount < _elementCount)
        {
            Create(mElementSize, mElementCount, _pData);
        }
        else
        {
            D3D11_MAPPED_SUBRESOURCE subResource = {};
            CONTEXT->Map(mpWriteBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
            memcpy(subResource.pData, _pData, mElementSize * _elementCount);
            CONTEXT->Unmap(mpWriteBuffer.Get(), 0);
        }

        CONTEXT->CopyResource(mpBuffer.Get(), mpWriteBuffer.Get());
    }
    void StructuredBuffer::GetData(void* _pData, int _elementSize)
    {
        CONTEXT->CopyResource(mpReadBuffer.Get(), mpBuffer.Get());
    }
    void StructuredBuffer::PushGraphicsData(RegisterSRV _eReg)
    {
        UINT regInt = static_cast<UINT>(_eReg);
        CONTEXT->VSSetShaderResources(regInt, 1, mpSRV.GetAddressOf());
        CONTEXT->GSSetShaderResources(regInt, 1, mpSRV.GetAddressOf());
        CONTEXT->PSSetShaderResources(regInt, 1, mpSRV.GetAddressOf());
        CONTEXT->CSSetShaderResources(regInt, 1, mpSRV.GetAddressOf());
        mSRVSlot = regInt;
    }
    void StructuredBuffer::PushComputeUAVData(RegisterUAV _eReg)
    {
        mUAVSlot = static_cast<UINT>(_eReg);
        CONTEXT->CSSetUnorderedAccessViews(mUAVSlot, 1, mpUAV.GetAddressOf(), 0);
    }
    void StructuredBuffer::ClearGraphicsData()
    {
        // Clear SRV
        CONTEXT->VSSetShaderResources(mSRVSlot, 1, reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));
        CONTEXT->DSSetShaderResources(mSRVSlot, 1, reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));
        CONTEXT->GSSetShaderResources(mSRVSlot, 1, reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));
        CONTEXT->HSSetShaderResources(mSRVSlot, 1, reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));
        CONTEXT->CSSetShaderResources(mSRVSlot, 1, reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));
        CONTEXT->PSSetShaderResources(mSRVSlot, 1, reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));

        // Clear UAV
        CONTEXT->CSSetUnorderedAccessViews(mUAVSlot, 1, reinterpret_cast<ID3D11UnorderedAccessView**>(&mppNullptr), 0);
    }
    void StructuredBuffer::CreateBuffer(void* _pInitialData)
    {
        D3D11_BUFFER_DESC desc = {};
        desc.ByteWidth = mElementSize * mElementCount;
        desc.StructureByteStride = mElementSize;
        desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
        desc.CPUAccessFlags = 0;
        desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS;
        desc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

        HRESULT hr = S_OK;
        if (nullptr != _pInitialData)
        {
            D3D11_SUBRESOURCE_DATA subResource = {};
            subResource.pSysMem = _pInitialData;
            hr = DEVICE->CreateBuffer(&desc, &subResource, mpBuffer.GetAddressOf());
        }
        else
        {
            hr = DEVICE->CreateBuffer(&desc, nullptr, mpBuffer.GetAddressOf());
        }
        AssertEx(SUCCEEDED(hr), L"StructuredBuffer::CreateBuffer() - 버퍼 생성 실패");
    }
    void StructuredBuffer::CreateView()
    {
        // Create SRV
        {
            D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
            srvDesc.BufferEx.NumElements = mElementCount;
            srvDesc.ViewDimension = D3D_SRV_DIMENSION_BUFFEREX;

            HRESULT hr = DEVICE->CreateShaderResourceView(mpBuffer.Get(), &srvDesc, mpSRV.GetAddressOf());
            AssertEx(SUCCEEDED(hr), L"StructuredBuffer::CreateView() - SRV 생성 실패");
        }

        // Create UAV
        {
            D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
            uavDesc.Buffer.NumElements = mElementCount;
            uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

            HRESULT hr = DEVICE->CreateUnorderedAccessView(mpBuffer.Get(), &uavDesc, mpUAV.GetAddressOf());
            AssertEx(SUCCEEDED(hr), L"StructuredBuffer::CreateView() - UAV 생성 실패");
        }
    }
    void StructuredBuffer::CreateRWBuffer()
    {
        // Create ReadBuffer
        {
            D3D11_BUFFER_DESC readDesc = { };
            readDesc.ByteWidth = mElementSize * mElementCount;
            readDesc.StructureByteStride = mElementSize;
            readDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
            readDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            readDesc.Usage = D3D11_USAGE_DEFAULT;
            readDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

            HRESULT hr = (DEVICE->CreateBuffer(&readDesc, nullptr, mpReadBuffer.GetAddressOf()));
            AssertEx(SUCCEEDED(hr), L"StructuredBuffer::CreateRWBuffer() - ReadBuffer 생성 실패");
        }

        // Create WriteBuffer
        {
            D3D11_BUFFER_DESC writeDesc = { };
            writeDesc.ByteWidth = mElementSize * mElementCount;
            writeDesc.StructureByteStride = mElementSize;
            writeDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
            writeDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            writeDesc.Usage = D3D11_USAGE_DYNAMIC;
            writeDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

            HRESULT hr = (DEVICE->CreateBuffer(&writeDesc, nullptr, mpWriteBuffer.GetAddressOf()));
            AssertEx(SUCCEEDED(hr), L"StructuredBuffer::CreateRWBuffer() - WriteBuffer 생성 실패");
        }
    }
}