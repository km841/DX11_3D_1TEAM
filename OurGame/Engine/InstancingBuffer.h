#pragma once

namespace hm
{
	struct InstancingParams
	{
		Matrix matWorld;
		Matrix matWV;
		Matrix matWVP;
	};

	class InstancingBuffer
	{
	public:
		void Initialize(UINT32 _bufferSize, UINT32 _maxCount = 4096);
		void ClearData();
		void AddData(InstancingParams& _params);
		void PushData();

		void SetID(UINT64 _instancingID) { mInstanceID = _instancingID; }
		UINT64 GetID() { return mInstanceID; }

	public:
		UINT32 GetDataCount() { return static_cast<UINT32>(mData.size()); }
		ComPtr<ID3D11Buffer> GetInstancingBuffer() { return mpInstancingBuffer; }

	private:
		UINT64 mInstanceID;
		ComPtr<ID3D11Buffer> mpInstancingBuffer;

		UINT32 mMaxCount;
		std::vector<InstancingParams> mData;

	};
}


