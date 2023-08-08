#include "pch.h"
#include "Mesh.h"
#include "Engine.h"
#include "FBXLoader.h"
#include "InstancingBuffer.h"
#include "Resources.h"

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
	}
	void Mesh::Initialize(const std::vector<Vertex>& _vertexBuffer, const std::vector<int>& _indexBuffer)
	{
		ComPtr<ID3D11Buffer> pVertexBuffer = CreateVertexBuffer(_vertexBuffer);
		std::vector<IndexBufferInfo> indexBufferInfo = {};
		indexBufferInfo.push_back(CreateIndexBuffer(_indexBuffer));
		mMeshContainerVec.push_back(new MeshContainer{ pVertexBuffer, indexBufferInfo });
	}
	void Mesh::Render(int _instanceCount, int _index)
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

	void Mesh::Render(InstancingBuffer* _pBuffer, int _index)
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

	shared_ptr<Mesh> Mesh::CreateFromFBX(const FbxMeshInfo* _pMeshInfo, FBXLoader& loader)
	{
		shared_ptr<Mesh> pMesh = make_shared<Mesh>();
		pMesh->SetHash(CreateHash(_pMeshInfo->vertices[0]));

		pMesh->CreateVertexBuffer(_pMeshInfo->vertices);

		for (const std::vector<int>& buffer : _pMeshInfo->indices)
		{
			if (buffer.empty())
			{
				std::vector<int> defaultBuffer{ 0 };
				pMesh->CreateIndexBuffer(defaultBuffer);
			}
			else
			{
				pMesh->CreateIndexBuffer(buffer);
			}
		}

		//if (meshInfo->bHasAnimation)
		//	mesh->CreateBonesAndAnimations(loader);

		return pMesh;
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
	void Mesh::AddMeshContainer(const FbxMeshInfo* meshInfo, FBXLoader& loader)
	{
		ComPtr<ID3D11Buffer> pVertexBuffer= CreateVertexBuffer(meshInfo->vertices);

		std::vector<IndexBufferInfo> indexBufferVec = {};
		for (const std::vector<int>& buffer : meshInfo->indices)
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

		MeshContainer* pMeshContainer = new MeshContainer{ pVertexBuffer , indexBufferVec };
		mMeshContainerVec.push_back(pMeshContainer);
	}
}