#include "pch.h"
#include "Mesh.h"
#include "Engine.h"
#include "FBXLoader.h"
#include "InstancingBuffer.h"
#include "Resources.h"
#include "StructuredBuffer.h"

namespace hm
{
	Mesh::Mesh()
		: Object(ObjectType::Mesh)
		, mHash(0)
	{
	}
	Mesh::~Mesh()
	{
		for (int i = 0; i < mMeshContainerVec.size(); ++i)
		{
			SAFE_DELETE(mMeshContainerVec[i]);
		}
		mMeshContainerVec.clear();


		for (int i = 0; i < mAnimContainerVec.size(); ++i)
		{
			SAFE_DELETE(mAnimContainerVec[i]);
		}
		mAnimContainerVec.clear();
	}
	void Mesh::Initialize(const std::vector<Vertex>& _vertexBuffer, const std::vector<int>& _indexBuffer)
	{
		ComPtr<ID3D11Buffer> pVertexBuffer = CreateVertexBuffer(_vertexBuffer);
		std::vector<IndexBufferInfo> indexBufferInfo = {};
		indexBufferInfo.push_back(CreateIndexBuffer(_indexBuffer));
		mMeshContainerVec.push_back(new MeshContainer{ pVertexBuffer, indexBufferInfo });
	}
	void Mesh::Render()
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		CONTEXT->IASetVertexBuffers(0, 1, mMeshContainerVec[0]->pVertexBuffer.GetAddressOf(), &stride, &offset);

		for (int i = 0; i < mMeshContainerVec[0]->indexBufferGroup.size(); ++i)
		{
			CONTEXT->IASetIndexBuffer(mMeshContainerVec[0]->indexBufferGroup[i].pBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			CONTEXT->DrawIndexed(mMeshContainerVec[0]->indexBufferGroup[i].count, 0, 0);
		}
	}
	void Mesh::RenderInstancing(int _instanceCount, int _index)
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		CONTEXT->IASetVertexBuffers(0, 1, mMeshContainerVec[_index]->pVertexBuffer.GetAddressOf(), &stride, &offset);

		for (int i = 0; i < mMeshContainerVec[_index]->indexBufferGroup.size(); ++i)
		{
			CONTEXT->IASetIndexBuffer(mMeshContainerVec[_index]->indexBufferGroup[i].pBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			CONTEXT->DrawIndexedInstanced(mMeshContainerVec[_index]->indexBufferGroup[i].count, _instanceCount, 0, 0, 0);
		}
	}

	void Mesh::RenderInstancing(InstancingBuffer* _pBuffer, int _index)
	{
		UINT strides[2] = { sizeof(Vertex), sizeof(InstancingParams)};
		UINT offset[2] = { 0, 0 };

		ID3D11Buffer* buffers[] = { mMeshContainerVec[_index]->pVertexBuffer.Get(), _pBuffer->GetInstancingBuffer().Get()};

		CONTEXT->IASetVertexBuffers(0, 2, buffers, strides, offset);

		for (int i = 0; i < mMeshContainerVec[_index]->indexBufferGroup.size(); ++i)
		{
			CONTEXT->IASetIndexBuffer(mMeshContainerVec[_index]->indexBufferGroup[i].pBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			CONTEXT->DrawIndexedInstanced(mMeshContainerVec[_index]->indexBufferGroup[i].count, _pBuffer->GetDataCount(), 0, 0, 0);
		}
	}

	ComPtr<ID3D11Buffer> Mesh::CreateVertexBuffer(const std::vector<Vertex>& _buffer)
	{
		UINT count = static_cast<UINT>(_buffer.size());
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = sizeof(Vertex) * count;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = _buffer.data();

		ComPtr<ID3D11Buffer> pVertexBuffer;

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &pVertexBuffer);
		AssertEx(SUCCEEDED(hr), L"Mesh::CreateVertexBuffer() - 버퍼 생성 실패!");

		return pVertexBuffer;
	}

	IndexBufferInfo Mesh::CreateIndexBuffer(const std::vector<int>& _buffer)
	{
		int indexCount = static_cast<int>(_buffer.size());
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = sizeof(int) * indexCount;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = _buffer.data();

		ComPtr<ID3D11Buffer> pIndexBuffer;

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &pIndexBuffer);
		AssertEx(SUCCEEDED(hr), L"Mesh::CreateIndexBuffer() - 버퍼 생성 실패!");

		IndexBufferInfo indexBufferInfo =
		{
			pIndexBuffer,
			indexCount,
		};

		return indexBufferInfo;
	}
	void Mesh::AddAnimContainer(FBXLoader& _loader)
	{
		// Animation Clip 데이터 로드
		AnimationContainer* pAnimContainer = new AnimationContainer;
		mAnimContainerVec.push_back(pAnimContainer);

		UINT32 frameCount = 0;
		std::vector<shared_ptr<FbxAnimClipInfo>>& animClips = _loader.GetAnimClip();

		std::vector<AnimClipInfo> animInfoVec = {};
		for (shared_ptr<FbxAnimClipInfo>& ac : animClips)
		{
			AnimClipInfo info = {};

			info.animName = ac->name;
			info.duration = ac->endTime.GetSecondDouble() - ac->startTime.GetSecondDouble();

			int startFrame = static_cast<int>(ac->startTime.GetFrameCount(ac->mode));
			int endFrame = static_cast<int>(ac->endTime.GetFrameCount(ac->mode));

			info.frameCount = endFrame - startFrame;
			info.keyFrames.resize(ac->keyFrames.size());

			const int boneCount = static_cast<int>(ac->keyFrames.size());
			for (int b = 0; b < boneCount; ++b)
			{
				auto& vec = ac->keyFrames[b];

				const int size = static_cast<int>(vec.size());
				frameCount = max(frameCount, static_cast<UINT32>(size));
				info.keyFrames[b].resize(size);

				for (int f = 0; f < size; ++f)
				{
					FbxKeyFrameInfo& kf = vec[f];
					KeyFrameInfo& kfInfo = info.keyFrames[b][f];

					kfInfo.time = kf.time;
					kfInfo.frame = static_cast<int>(size);
					kfInfo.scale.x = static_cast<float>(kf.matTransform.GetS().mData[0]);
					kfInfo.scale.y = static_cast<float>(kf.matTransform.GetS().mData[1]);
					kfInfo.scale.z = static_cast<float>(kf.matTransform.GetS().mData[2]);
					kfInfo.rotation.x = static_cast<float>(kf.matTransform.GetQ().mData[0]);
					kfInfo.rotation.y = static_cast<float>(kf.matTransform.GetQ().mData[1]);
					kfInfo.rotation.z = static_cast<float>(kf.matTransform.GetQ().mData[2]);
					kfInfo.rotation.w = static_cast<float>(kf.matTransform.GetQ().mData[3]);
					kfInfo.translate.x = static_cast<float>(kf.matTransform.GetT().mData[0]);
					kfInfo.translate.y = static_cast<float>(kf.matTransform.GetT().mData[1]);
					kfInfo.translate.z = static_cast<float>(kf.matTransform.GetT().mData[2]);
				}
			}

			animInfoVec.push_back(info);
		}

		pAnimContainer->animClips = animInfoVec;


		// Bone 데이터 로드
		std::vector<shared_ptr<FbxBoneInfo>>& bones = _loader.GetBones();
		std::vector<BoneInfo> boneInfoVec = {};
		for (shared_ptr<FbxBoneInfo>& pBone : bones)
		{
			BoneInfo boneInfo = {};
			boneInfo.parentIdx = pBone->parentIndex;
			boneInfo.matOffset = GetMatrix(pBone->matOffset);
			boneInfo.boneName = pBone->boneName;
			boneInfoVec.push_back(boneInfo);
		}

		pAnimContainer->bones = boneInfoVec;

		// Skin 데이터 로드

		if (true == IsAnimMesh())
		{
			shared_ptr<StructuredBuffer> pOffsetBuffer = make_shared<StructuredBuffer>();
			std::vector<shared_ptr<StructuredBuffer>> frameBuffer = {};

			const int boneCount = static_cast<int>(pAnimContainer->bones.size());
			std::vector<Matrix> offsetVec(boneCount);

			for (size_t b = 0; b < boneCount; ++b)
				offsetVec[b] = pAnimContainer->bones[b].matOffset;

			pOffsetBuffer->Create(sizeof(Matrix), static_cast<UINT32>(offsetVec.size()), offsetVec.data());
			pAnimContainer->pOffsetBuffer = pOffsetBuffer;

			const int animCount = static_cast<int>(pAnimContainer->animClips.size());
			for (int i = 0; i < animCount; i++)
			{
				AnimClipInfo& animClip = pAnimContainer->animClips[i];

				// 애니메이션 프레임 정보
				std::vector<AnimFrameParams> frameParams;
				frameParams.resize(pAnimContainer->bones.size() * animClip.frameCount * 10);

				for (int b = 0; b < boneCount; b++)
				{
					const int keyFrameCount = static_cast<int>(animClip.keyFrames[b].size());
					for (int f = 0; f < keyFrameCount; f++)
					{
						int idx = static_cast<int>(boneCount * f + b);

						frameParams[idx] = AnimFrameParams
						{
							Vec4(animClip.keyFrames[b][f].scale),
							animClip.keyFrames[b][f].rotation, // Quaternion
							Vec4(animClip.keyFrames[b][f].translate)
						};
					}
				}
				frameBuffer.push_back(make_shared<StructuredBuffer>());
				frameBuffer.back()->Create(sizeof(AnimFrameParams), static_cast<UINT32>(frameParams.size()), frameParams.data());
			}

			pAnimContainer->frameBuffer = frameBuffer;
		}
	}
	Matrix Mesh::GetMatrix(const FbxAMatrix& _matrix)
	{
		Matrix mat;

		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 4; ++x)
			{
				mat.m[y][x] = static_cast<float>(_matrix.Get(y, x));
			}
		}

		return mat;
	}
	UINT32 Mesh::CreateHash(const Vertex& _vtx)
	{
		size_t hash = 0;
		//hash_combine(hash, std::hash<float>{}(_vtx.pos.x));
		//hash_combine(hash, std::hash<float>{}(_vtx.pos.y));
		//hash_combine(hash, std::hash<float>{}(_vtx.pos.z));
		hash_combine(hash, std::hash<float>{}(_vtx.normal.x));
		hash_combine(hash, std::hash<float>{}(_vtx.normal.y));
		hash_combine(hash, std::hash<float>{}(_vtx.normal.z));
		hash_combine(hash, std::hash<float>{}(_vtx.uv.x));
		hash_combine(hash, std::hash<float>{}(_vtx.uv.y));
		return static_cast<UINT32>(hash);
	}
	void Mesh::AddMeshContainer(const FbxMeshInfo* _pMeshInfo, FBXLoader& _loader)
	{
		ComPtr<ID3D11Buffer> pVertexBuffer= CreateVertexBuffer(_pMeshInfo->vertices);

		std::vector<IndexBufferInfo> indexBufferVec = {};
		for (const std::vector<int>& buffer : _pMeshInfo->indices)
		{
			if (buffer.empty())
			{
				std::vector<int> defaultBuffer{ 0 };
				indexBufferVec.push_back(CreateIndexBuffer(defaultBuffer));
			}
			else
			{
				indexBufferVec.push_back(CreateIndexBuffer(buffer));
			}
		}

		if (_pMeshInfo->bHasAnimation)
		{
			AddAnimContainer(_loader);
		}

		MeshContainer* pMeshContainer = new MeshContainer{ pVertexBuffer , indexBufferVec };
		pMeshContainer->bHasAnimation = _pMeshInfo->bHasAnimation;
		mMeshContainerVec.push_back(pMeshContainer);
	}
}