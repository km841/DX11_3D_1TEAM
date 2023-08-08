#pragma once
#include "Object.h"

namespace hm
{
    struct IndexBufferInfo
    {
        ComPtr<ID3D11Buffer>		pBuffer;
        int						    count;
    };

    struct MeshContainer
    {
        ComPtr<ID3D11Buffer>         pVertexBuffer;
        std::vector<IndexBufferInfo> indexBufferGroup;
    };

    struct FbxMeshInfo;
    class FBXLoader;
    class InstancingBuffer;
	class Mesh :
		public Object
	{
    public:
        Mesh();
        virtual ~Mesh();

        /* VertexBuffer와 IndexBuffer를 받아서 메쉬를 생성하는 함수
        * _vertexBuffer : 정점 정보들을 담은 벡터를 전달
        * _indexBuffer : 인덱스 정보를 담은 벡터를 전달
        */
        void Initialize(const std::vector<Vertex>& _vertexBuffer, const std::vector<int>& _indexBuffer);

        /*DrawIndexedInstanced를 실행하는 함수
        * 내부적으로 IASetVertexBuffer와 IASetIndexBuffer를 실행한다.
        * _instanceCount : 인스턴싱할 개수
        */
        void Render(int _instanceCount = 1, int _index = 0);
        void Render(InstancingBuffer* _pBuffer, int _index = 0);

        static shared_ptr<Mesh> CreateFromFBX(const FbxMeshInfo* meshInfo, FBXLoader& loader);
        static UINT32 CreateHash(const Vertex& _vtx);
        void SetHash(UINT32 _hash) { mHash = _hash; }
        UINT32 GetHash() { return mHash; }

        void AddMeshContainer(const struct FbxMeshInfo* meshInfo, FBXLoader& loader);
        UINT32 GetMeshContainerCount() { return static_cast<UINT32>(mMeshContainerVec.size()); }

    public:
        // 정점 정보를 통해 정점 버퍼를 생성하는 함수
        ComPtr<ID3D11Buffer> CreateVertexBuffer(const std::vector<Vertex>& _buffer);
        // 인덱스 정보를 통해 인덱스 버퍼를 생성하는 함수
        IndexBufferInfo CreateIndexBuffer(const std::vector<int>& _buffer);

    private:

    private:
        std::vector<MeshContainer*> mMeshContainerVec;
        UINT32 mHash;
	};
}


