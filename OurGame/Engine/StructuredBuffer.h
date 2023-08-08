#pragma once

namespace hm
{
	/*
	* 셰이더에서 사용하는 구조화버퍼 클래스
	*/
	class StructuredBuffer
	{
	public:
		StructuredBuffer();
		~StructuredBuffer();

	public:
		void Create(int _elementSize, int _elementCount, void* _pInitialData = nullptr, bool _bCpuAccess = false);
		void SetData(void* _pData, int _elementCount);
		void GetData(void* _pData, int _elementSize = 0);
		void PushGraphicsData(RegisterSRV _eReg);
		void PushComputeUAVData(RegisterUAV _eReg);
		void ClearGraphicsData();

		int GetElementSize() { return mElementSize; }
		int GetElementCount() { return mElementCount; }

	private:
		void CreateBuffer(void* _pInitialData);
		void CreateView();
		void CreateRWBuffer();

	private:
		ComPtr<ID3D11Buffer> mpWriteBuffer;
		ComPtr<ID3D11Buffer> mpReadBuffer;
		ComPtr<ID3D11Buffer> mpBuffer;

		ComPtr<ID3D11ShaderResourceView>  mpSRV;
		ComPtr<ID3D11UnorderedAccessView> mpUAV;

		int mElementSize;
		int mElementCount;

		UINT mSRVSlot;
		UINT mUAVSlot;

		void** mppNullptr;

	};
}


