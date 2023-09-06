#pragma once
#include "Object.h"

namespace hm
{
    class StructuredBuffer;
    struct IndexBufferInfo
    {
        ComPtr<ID3D11Buffer>		pBuffer;
        UINT32						    count;
        void*                   pData;
    };

    struct VertexBufferInfo
    {
        ComPtr<ID3D11Buffer>        pBuffer;
        UINT32                         count;
        void*                     pData;
    };

    struct MeshContainer
    {
        VertexBufferInfo             vertexBufferInfo;
        std::vector<IndexBufferInfo> indexBufferGroup;
        bool bHasAnimation = false;
    };

    struct FrameInfo
    {

    };

    struct KeyFrameInfo
    {
        double	time;
        int	    frame;
        Vec3	scale;
        Vec4	rotation;
        Vec3	translate;
    };

    struct BoneInfo
    {
        wstring	boneName;
        int		parentIdx;
        Matrix	matOffset;
    };

    struct AnimClipInfo
    {
        wstring			animName;
        int			    frameCount;
        double			duration;
        std::vector<std::vector<KeyFrameInfo>>	keyFrames;
        bool            bLoop = false;
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
        void Render();
        void RenderInstancing(int _instanceCount = 1, int _index = 0);
        void RenderInstancing(InstancingBuffer* _pBuffer, int _index = 0);

        static UINT32 CreateHash(const Vertex& _vtx);
        void SetHash(UINT32 _hash) { mHash = _hash; }
        UINT32 GetHash() { return mHash; }

        void AddMeshContainer(const FbxMeshInfo* _pMeshInfo, FBXLoader& _loader);
        void AddMeshContainer(MeshContainer* _pMeshContainer);
        void ClearMeshContainers();
        void CreateBonesAndAnimations(FBXLoader& _loader);
        UINT32 GetMeshContainerCount() { return static_cast<UINT32>(mMeshContainerVec.size()); }
        MeshContainer* GetMeshContainer(int _containerIndex);

        void SaveBoneAndAnimations(FILE* _pFile);
        void LoadBoneAndAnimations(FILE* _pFile);

    public:
        // 정점 정보를 통해 정점 버퍼를 생성하는 함수
        VertexBufferInfo CreateVertexBuffer(const std::vector<Vertex>& _buffer);
        VertexBufferInfo CreateVertexBuffer(void* _pVtxData, UINT32 _size);
        // 인덱스 정보를 통해 인덱스 버퍼를 생성하는 함수
        IndexBufferInfo CreateIndexBuffer(const std::vector<int>& _buffer);
        IndexBufferInfo CreateIndexBuffer(void* _pIdxData, UINT32 _size);

    public:
        std::vector<BoneInfo>*     GetBones() { return &mBones; }
        UINT32						     GetBoneCount() { return static_cast<UINT32>(mBones.size()); }
        std::vector<AnimClipInfo>* GetAnimClip() { return &mAnimClips; }

        bool							 IsAnimMesh() { return !mAnimClips.empty(); }
        shared_ptr<StructuredBuffer>	 GetBoneFrameDataBuffer(int index = 0) { return frameBuffer[index]; } // 전체 본 프레임 정보
        shared_ptr<StructuredBuffer>	 GetBoneOffsetBuffer() { return  pOffsetBuffer; }

    private:
        
        Matrix GetMatrix(const FbxAMatrix& _matrix); // FbxAMatrix -> XMMATRIX

    private:
        std::vector<MeshContainer*>      mMeshContainerVec;

        std::vector<AnimClipInfo> mAnimClips;
        std::vector<BoneInfo> mBones;

        shared_ptr<StructuredBuffer>              pOffsetBuffer;
        std::vector<shared_ptr<StructuredBuffer>> frameBuffer;

        UINT32 mHash;
	};
}


