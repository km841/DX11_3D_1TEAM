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
		ClearMeshContainers();
	}
	void Mesh::Initialize(const std::vector<Vertex>& _vertexBuffer, const std::vector<int>& _indexBuffer)
	{
		VertexBufferInfo vertexBufferInfo = CreateVertexBuffer(_vertexBuffer);

		std::vector<IndexBufferInfo> indexBufferInfoVec = {};
		IndexBufferInfo indexBufferInfo = CreateIndexBuffer(_indexBuffer);
		indexBufferInfoVec.push_back(indexBufferInfo);

		MeshContainer* pMeshContainer = new MeshContainer;
		pMeshContainer->vertexBufferInfo = vertexBufferInfo;
		pMeshContainer->indexBufferGroup = indexBufferInfoVec;

		mMeshContainerVec.push_back(pMeshContainer);
	}
	void Mesh::Render()
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		UINT32 meshCount = mMeshContainerVec.size();

		for (UINT32 c = 0; c < meshCount; ++c)
		{
			CONTEXT->IASetVertexBuffers(0, 1, mMeshContainerVec[c]->vertexBufferInfo.pBuffer.GetAddressOf(), &stride, &offset);

			for (int i = 0; i < mMeshContainerVec[c]->indexBufferGroup.size(); ++i)
			{
				CONTEXT->IASetIndexBuffer(mMeshContainerVec[c]->indexBufferGroup[i].pBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
				CONTEXT->DrawIndexed(mMeshContainerVec[c]->indexBufferGroup[i].count, 0, 0);
			}
		}


	}
	void Mesh::Render(int _index)
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		CONTEXT->IASetVertexBuffers(0, 1, mMeshContainerVec[_index]->vertexBufferInfo.pBuffer.GetAddressOf(), &stride, &offset);

		for (int i = 0; i < mMeshContainerVec[_index]->indexBufferGroup.size(); ++i)
		{
			CONTEXT->IASetIndexBuffer(mMeshContainerVec[_index]->indexBufferGroup[i].pBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			CONTEXT->DrawIndexed(mMeshContainerVec[_index]->indexBufferGroup[i].count, 0, 0);
		}
	}
	void Mesh::RenderInstancing(int _instanceCount, int _index)
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		CONTEXT->IASetVertexBuffers(0, 1, mMeshContainerVec[_index]->vertexBufferInfo.pBuffer.GetAddressOf(), &stride, &offset);

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

		ID3D11Buffer* buffers[] = { mMeshContainerVec[_index]->vertexBufferInfo.pBuffer.Get(), _pBuffer->GetInstancingBuffer().Get()};

		CONTEXT->IASetVertexBuffers(0, 2, buffers, strides, offset);

		for (int i = 0; i < mMeshContainerVec[_index]->indexBufferGroup.size(); ++i)
		{
			CONTEXT->IASetIndexBuffer(mMeshContainerVec[_index]->indexBufferGroup[i].pBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			CONTEXT->DrawIndexedInstanced(mMeshContainerVec[_index]->indexBufferGroup[i].count, _pBuffer->GetDataCount(), 0, 0, 0);
		}
	}

	VertexBufferInfo Mesh::CreateVertexBuffer(const std::vector<Vertex>& _buffer)
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

		VertexBufferInfo vtxInfo = {};
		vtxInfo.pBuffer = pVertexBuffer;
		vtxInfo.count = count;
		vtxInfo.pData = new char[_buffer.size() * sizeof(Vertex)];
		memcpy(vtxInfo.pData, _buffer.data(), _buffer.size() * sizeof(Vertex));

		return vtxInfo;
	}

	VertexBufferInfo Mesh::CreateVertexBuffer(void* _pVtxData, UINT32 _size)
	{
		UINT count = _size;
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = sizeof(Vertex) * count;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = _pVtxData;

		ComPtr<ID3D11Buffer> pVertexBuffer;

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &pVertexBuffer);
		AssertEx(SUCCEEDED(hr), L"Mesh::CreateVertexBuffer() - 버퍼 생성 실패!");

		VertexBufferInfo vtxInfo = {};
		vtxInfo.pBuffer = pVertexBuffer;
		vtxInfo.count = count;
		vtxInfo.pData = new char[count * sizeof(Vertex)];
		memcpy(vtxInfo.pData, _pVtxData, count * sizeof(Vertex));

		return vtxInfo;
	}

	IndexBufferInfo Mesh::CreateIndexBuffer(const std::vector<int>& _buffer)
	{
		UINT32 indexCount = static_cast<UINT32>(_buffer.size());
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

		indexBufferInfo.pData = new char[sizeof(int) * _buffer.size()];
		memcpy(indexBufferInfo.pData, _buffer.data(), sizeof(int) * _buffer.size());

		return indexBufferInfo;
	}
	IndexBufferInfo Mesh::CreateIndexBuffer(void* _pIdxData, UINT32 _size)
	{
		UINT32 indexCount = _size;
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = sizeof(int) * indexCount;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = _pIdxData;

		ComPtr<ID3D11Buffer> pIndexBuffer;

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &pIndexBuffer);
		AssertEx(SUCCEEDED(hr), L"Mesh::CreateIndexBuffer() - 버퍼 생성 실패!");

		IndexBufferInfo indexBufferInfo =
		{
			pIndexBuffer,
			indexCount,
		};

		indexBufferInfo.pData = new char[sizeof(int) * _size];
		memcpy(indexBufferInfo.pData, _pIdxData, sizeof(int) * _size);

		return indexBufferInfo;
	}
	void Mesh::CreateBonesAndAnimations(FBXLoader& _loader)
	{
		// Animation Clip 데이터 로드

#pragma region AnimClip
		UINT32 frameCount = 0;
		std::vector<shared_ptr<FbxAnimClipInfo>>& animClips = _loader.GetAnimClip();
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
			for (int b = 0; b < boneCount; b++)
			{
				auto& vec = ac->keyFrames[b];

				const int size = static_cast<int>(vec.size());
				frameCount = max(frameCount, static_cast<UINT32>(size));
				info.keyFrames[b].resize(size);

				for (int f = 0; f < size; f++)
				{
					FbxKeyFrameInfo& kf = vec[f];
					// FBX에서 파싱한 정보들로 채워준다
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

			mAnimClips.push_back(info);
		}
#pragma endregion

#pragma region Bones
		std::vector<shared_ptr<FbxBoneInfo>>& bones = _loader.GetBones();
		for (shared_ptr<FbxBoneInfo>& bone : bones)
		{
			BoneInfo boneInfo = {};
			boneInfo.parentIdx = bone->parentIndex;
			boneInfo.matOffset = GetMatrix(bone->matOffset);
			boneInfo.boneName = bone->boneName;
			mBones.push_back(boneInfo);
		}
#pragma endregion

#pragma region SkinData
		if (true == IsAnimMesh())
		{
			// BoneOffet 행렬
			const int boneCount = static_cast<int>(mBones.size());
			std::vector<Matrix> offsetVec(boneCount);
			for (size_t b = 0; b < boneCount; b++)
				offsetVec[b] = mBones[b].matOffset;

			// OffsetMatrix StructuredBuffer 세팅
			pOffsetBuffer = make_shared<StructuredBuffer>();
			pOffsetBuffer->Create(sizeof(Matrix), static_cast<UINT32>(offsetVec.size()), offsetVec.data());

			const int animCount = static_cast<int>(animClips.size());
			for (int i = 0; i < animCount; i++)
			{
				AnimClipInfo& animClip = mAnimClips[i];

				// 애니메이션 프레임 정보
				std::vector<AnimFrameParams> frameParams;
				for (int b = 0; b < boneCount; b++)
				{
					const int keyFrameCount = static_cast<int>(animClip.keyFrames[b].size());

					for (int f = 0; f < keyFrameCount; f++)
					{
						int idx = static_cast<int>(boneCount * f + b);
						if (idx >= frameParams.size())
							frameParams.resize(idx + 1);

						frameParams[idx] = AnimFrameParams
						{
							Vec4(animClip.keyFrames[b][f].scale),
							animClip.keyFrames[b][f].rotation, // Quaternion
							Vec4(animClip.keyFrames[b][f].translate)
						};
					}
				}

				// StructuredBuffer 세팅
				frameBuffer.push_back(make_shared<StructuredBuffer>());
				frameBuffer.back()->Create(sizeof(AnimFrameParams), static_cast<UINT32>(frameParams.size()), frameParams.data());
			}
		}

	}
	MeshContainer* Mesh::GetMeshContainer(int _containerIndex)
	{
		AssertEx(_containerIndex < mMeshContainerVec.size(), L"Mesh::GetMeshContainer() - 인덱스가 메쉬 컨테이너의 개수를 초과");
		return mMeshContainerVec[_containerIndex];
	}
	void Mesh::SaveBoneAndAnimations(FILE* _pFile)
	{
		AssertEx(nullptr != _pFile, L"Mesh::AnimationSave() - 파일포인터가 nullptr이다");

		// Save Anim Clips
		UINT32 animClipCount = static_cast<UINT32>(mAnimClips.size());
		fwrite(&animClipCount, sizeof(UINT32), 1, _pFile);

		for (UINT32 i = 0; i < animClipCount; ++i)
		{
			UINT32 animNameCount = static_cast<UINT32>(mAnimClips[i].animName.size());
			fwrite(&animNameCount, sizeof(UINT32), 1, _pFile);
			fwrite(mAnimClips[i].animName.c_str(), sizeof(wchar_t), animNameCount, _pFile);
			fwrite(&mAnimClips[i].frameCount, sizeof(int), 1, _pFile);
			fwrite(&mAnimClips[i].duration, sizeof(double), 1, _pFile);

			UINT32 keyFrameRow = static_cast<UINT32>(mAnimClips[i].keyFrames.size());
			fwrite(&keyFrameRow, sizeof(UINT32), 1, _pFile);

			for (UINT32 y = 0; y < keyFrameRow; ++y)
			{
				UINT32 keyFrameCol = static_cast<UINT32>(mAnimClips[i].keyFrames[y].size());
				fwrite(&keyFrameCol, sizeof(UINT32), 1, _pFile);

				for (UINT32 x = 0; x < keyFrameCol; ++x)
				{
					KeyFrameInfo& info = mAnimClips[i].keyFrames[y][x];

					fwrite(&info.time, sizeof(double), 1, _pFile);
					fwrite(&info.frame, sizeof(int), 1, _pFile);
					fwrite(&info.scale, sizeof(Vec3), 1, _pFile);
					fwrite(&info.rotation, sizeof(Vec4), 1, _pFile);
					fwrite(&info.translate, sizeof(Vec3), 1, _pFile);
				}
			}
		}

		// Save Bones
		UINT32 boneCount = static_cast<UINT32>(mBones.size());
		fwrite(&boneCount, sizeof(UINT32), 1, _pFile);

		for (UINT32 i = 0; i < boneCount; ++i)
		{
			UINT32 boneNameCount = static_cast<UINT32>(mBones[i].boneName.size());
			fwrite(&boneNameCount, sizeof(UINT32), 1, _pFile);
			fwrite(mBones[i].boneName.c_str(), sizeof(wchar_t), boneNameCount, _pFile);

			fwrite(&mBones[i].parentIdx, sizeof(int), 1, _pFile);
			fwrite(&mBones[i].matOffset.m, sizeof(Matrix), 1, _pFile);
		}
	}

	void Mesh::LoadBoneAndAnimations(FILE* _pFile)
	{
		AssertEx(nullptr != _pFile, L"Mesh::LoadBoneAndAnimations() - 파일포인터가 nullptr이다");
		mAnimClips.clear();
		mBones.clear();

		// Load Anim Clips
		UINT32 animClipCount = 0;
		fread(&animClipCount, sizeof(UINT32), 1, _pFile);

		for (UINT32 i = 0; i < animClipCount; ++i)
		{
			mAnimClips.push_back(AnimClipInfo());
			AnimClipInfo& animClipInfo = mAnimClips.back();

			UINT32 animNameCount = 0;
			fread(&animNameCount, sizeof(UINT32), 1, _pFile);
			animClipInfo.animName.resize(animNameCount);
			fread(animClipInfo.animName.data(), sizeof(wchar_t), animNameCount, _pFile);
			fread(&animClipInfo.frameCount, sizeof(int), 1, _pFile);
			fread(&animClipInfo.duration, sizeof(double), 1, _pFile);

			UINT32 keyFrameRow = 0;
			fread(&keyFrameRow, sizeof(UINT32), 1, _pFile);
			animClipInfo.keyFrames.resize(keyFrameRow);

			for (UINT32 y = 0; y < keyFrameRow; ++y)
			{
				UINT32 keyFrameCol = 0;
				fread(&keyFrameCol, sizeof(UINT32), 1, _pFile);
				animClipInfo.keyFrames[y].resize(keyFrameCol);

				for (UINT32 x = 0; x < keyFrameCol; ++x)
				{
					fread(&animClipInfo.keyFrames[y][x].time, sizeof(double), 1, _pFile);
					fread(&animClipInfo.keyFrames[y][x].frame, sizeof(int), 1, _pFile);
					fread(&animClipInfo.keyFrames[y][x].scale, sizeof(Vec3), 1, _pFile);
					fread(&animClipInfo.keyFrames[y][x].rotation, sizeof(Vec4), 1, _pFile);
					fread(&animClipInfo.keyFrames[y][x].translate, sizeof(Vec3), 1, _pFile);
				}
			}
		}

		// Load Bones
		{
			UINT32 boneCount = 0;
			fread(&boneCount, sizeof(UINT32), 1, _pFile);

			for (UINT32 i = 0; i < boneCount; ++i)
			{
				mBones.push_back(BoneInfo());
				BoneInfo& boneInfo = mBones.back();

				UINT32 boneNameCount = 0;
				fread(&boneNameCount, sizeof(UINT32), 1, _pFile);
				boneInfo.boneName.resize(boneNameCount);
				fread(boneInfo.boneName.data(), sizeof(wchar_t), boneNameCount, _pFile);

				fread(&boneInfo.parentIdx, sizeof(int), 1, _pFile);
				fread(&boneInfo.matOffset.m, sizeof(Matrix), 1, _pFile);
			}
		}


		// Create Skin Data
		// BoneOffet 행렬
		const int boneCount = static_cast<int>(mBones.size());
		std::vector<Matrix> offsetVec(boneCount);
		for (size_t b = 0; b < boneCount; b++)
			offsetVec[b] = mBones[b].matOffset;

		// OffsetMatrix StructuredBuffer 세팅
		pOffsetBuffer = make_shared<StructuredBuffer>();
		pOffsetBuffer->Create(sizeof(Matrix), static_cast<UINT32>(offsetVec.size()), offsetVec.data());

		const int animCount = static_cast<int>(mAnimClips.size());
		for (int i = 0; i < animCount; i++)
		{
			AnimClipInfo& animClip = mAnimClips[i];

			// 애니메이션 프레임 정보
			std::vector<AnimFrameParams> frameParams;

			for (int b = 0; b < boneCount; b++)
			{
				const int keyFrameCount = static_cast<int>(animClip.keyFrames[b].size());

				for (int f = 0; f < keyFrameCount; f++)
				{
					int idx = static_cast<int>(boneCount * f + b);
					if (idx >= frameParams.size())
						frameParams.resize(idx + 1);

					frameParams[idx] = AnimFrameParams
					{
						Vec4(animClip.keyFrames[b][f].scale),
						animClip.keyFrames[b][f].rotation, // Quaternion
						Vec4(animClip.keyFrames[b][f].translate)
					};
				}
			}

			// StructuredBuffer 세팅
			frameBuffer.push_back(make_shared<StructuredBuffer>());
			frameBuffer.back()->Create(sizeof(AnimFrameParams), static_cast<UINT32>(frameParams.size()), frameParams.data());
		}

	}

	TriangleMeshInfo Mesh::GetTriangleMeshInfo()
	{
		TriangleMeshInfo info = {};

		UINT32 totalVertices = 0;
		UINT32 totalIndices = 0;
		
		int vtxAccCount = 0;
		int idxAccCount = 0;

		for (int i = 0; i < mMeshContainerVec.size(); ++i)
		{
			totalVertices += mMeshContainerVec[i]->vertexBufferInfo.count;
			totalIndices += mMeshContainerVec[i]->indexBufferGroup[0].count;
		}

		info.vertices.resize(totalVertices);
		info.indices.resize(totalIndices);

		for (int i = 0; i < mMeshContainerVec.size(); ++i)
		{
			UINT32 verticeCount = mMeshContainerVec[i]->vertexBufferInfo.count;
			int vertexSize = sizeof(Vertex);
			int vertexOffset = 0;
			for (UINT32 j = 0; j < verticeCount; ++j)
			{
				Vertex* v = new Vertex;
				memcpy(v, (char*)mMeshContainerVec[i]->vertexBufferInfo.pData + vertexOffset, vertexSize);
				info.vertices[vtxAccCount + j] = (*v).pos;
				vertexOffset += vertexSize;
				SAFE_DELETE(v);
			}

			UINT32 indicesCount = mMeshContainerVec[i]->indexBufferGroup[0].count;
			int indexSize = sizeof(int);
			int indexOffset = 0;

			for (UINT32 j = 0; j < indicesCount; ++j)
			{
				int* idx = new int;
				memcpy(idx, (char*)mMeshContainerVec[i]->indexBufferGroup[0].pData + indexOffset, indexSize);
				info.indices[idxAccCount + j] = vtxAccCount + *idx;
				indexOffset += indexSize;
				SAFE_DELETE(idx);
			}

			vtxAccCount += verticeCount;
			idxAccCount += indicesCount;
		}

		return info;
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
		VertexBufferInfo bufferInfo = CreateVertexBuffer(_pMeshInfo->vertices);

		std::vector<IndexBufferInfo> indexBufferVec = {};
		for (const std::vector<int>& buffer : _pMeshInfo->indices)
		{
			IndexBufferInfo indexBufferInfo = {};

			if (buffer.empty())
			{
				std::vector<int> defaultBuffer{ 0 };
				indexBufferInfo = CreateIndexBuffer(defaultBuffer);
			}
			else
			{
				indexBufferInfo = CreateIndexBuffer(buffer);
			}

			indexBufferVec.push_back(indexBufferInfo);
		}

		MeshContainer* pMeshContainer = new MeshContainer;
		pMeshContainer->vertexBufferInfo = bufferInfo;
		pMeshContainer->indexBufferGroup = indexBufferVec;
		pMeshContainer->bHasAnimation = _pMeshInfo->bHasAnimation;
		mMeshContainerVec.push_back(pMeshContainer);
	}
	void Mesh::AddMeshContainer(MeshContainer* _pMeshContainer)
	{
		mMeshContainerVec.push_back(_pMeshContainer);
	}
	void Mesh::ClearMeshContainers()
	{
		for (int i = 0; i < mMeshContainerVec.size(); ++i)
		{
			SAFE_DELETE_ARRAY(mMeshContainerVec[i]->vertexBufferInfo.pData);
			
			for (int j = 0; j < mMeshContainerVec[i]->indexBufferGroup.size(); ++j)
			{
				SAFE_DELETE_ARRAY(mMeshContainerVec[i]->indexBufferGroup[j].pData);
			}

			SAFE_DELETE(mMeshContainerVec[i]);
		}
		mMeshContainerVec.clear();
	}
}