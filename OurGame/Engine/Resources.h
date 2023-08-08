#pragma once
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include "MeshData.h"
#include "GameObject.h"

namespace hm
{
	class Resources
	{
		DECLARE_SINGLE(Resources);

	public:
		// 자주 사용할 셰이더와 머티리얼을 생성하는 함수
		void Initialize();

		// 수동으로 제거할 필요가 있는 리소스를 삭제하는 함수
		void Destroy();

		/* 사이즈에 맞는 텍스쳐를 생성하는 함수
		* _name : Resources를 통해 이 리소스를 찾을 수 있는 키 값
		* _eFormat : 텍스쳐 포맷 (DXGI_FORMAT_D24_UNORM_S8_UINT..)
		* _eTextureFormat : 사용할 텍스쳐 타입 (RTV, SRV, UAV 등등), 이 포맷을 기준으로 View를 만든다
		* _width : 텍스쳐의 가로 크기
		* _height : 텍스쳐의 세로 크기
		*/
		shared_ptr<Texture> CreateTexture(const wstring& _name, DXGI_FORMAT _eFormat, UINT32 _eTextureType, int _width, int _height);

		/*이미 리소스가 존재하는 경우 그 리소스를 이용해 텍스쳐를 만드는 함수
		* _name : Resources를 통해 이 리소스를 찾을 수 있는 키 값
		* _eFormat : 텍스쳐 포맷 (DXGI_FORMAT_D24_UNORM_S8_UINT..)
		* _eTextureFormat : 사용할 텍스쳐 타입 (RTV, SRV, UAV 등등), 이 포맷을 기준으로 View를 만든다
		*/ 
		shared_ptr<Texture> CreateTextureFromResource(const wstring& _name, DXGI_FORMAT _eFormat, UINT32 _eTextureType, ComPtr<ID3D11Texture2D> _tex2D);


		shared_ptr<MeshData> LoadFBX(const wstring& _path);

		/* 리소스를 로드하는 함수
		* _key : 불러올 리소스의 키
		* _path : 만약 리소스가 없다면 불러올 리소스의 경로
		*/
		template<typename T>
		shared_ptr<T> Load(const wstring& _key, const wstring& _path);


		/* 리소스를 등록하는 함수
		* _key : 저장할 리소스의 키
		* _pObject : 저장할 오브젝트의 스마트 포인터
		*/
		template<typename T>
		bool Add(const wstring& _key, shared_ptr<T> _pObject);

		/* 리소스를 불러오는 함수
		* _key : 불러올 리소스의 키
		*/
		template<typename T>
		shared_ptr<T> Get(const wstring& _key);

		/* Add, Get, Load 등의 함수들을 템플릿으로 사용할 수 있게 해주는 함수 
		* 내부적으로 타입 T를 클래스와 매핑하여 적절한 enum값으로 반환해준다.
		*/
		template<typename T>
		ObjectType GetObjectType();

		// Rect Mesh를 반환한다.
		shared_ptr<Mesh> LoadRectMesh();
		// Circle Mesh를 반환한다.
		shared_ptr<Mesh> LoadCircleMesh();
		// Point Mesh를 반환한다.
		shared_ptr<Mesh> LoadPointMesh();

		shared_ptr<Mesh> LoadCubeMesh();
		shared_ptr<Mesh> LoadSphereMesh();
		shared_ptr<Mesh> LoadBoundingCubeMesh();

		// 자주 사용할 Shader를 생성한다.
		void CreateDefaultShader();
		// 자주 사용할 Material을 생성한다.
		void CreateDefaultMaterial();

	private:
		using KeyObjMap = std::map<wstring, shared_ptr<Object>>;
		std::array<KeyObjMap, OBJECT_TYPE_COUNT> mResources;
	};
	template<typename T>
	inline shared_ptr<T> Resources::Load(const wstring& _key, const wstring& _path)
	{
		ObjectType eObjType = GetObjectType<T>();
		KeyObjMap& mObjMap = mResources[static_cast<int>(eObjType)];

		auto findIt = mObjMap.find(_key);
		if (mObjMap.end() != findIt)
			return static_pointer_cast<T>(findIt->second);

		shared_ptr<T> pObject = make_shared<T>();
		pObject->SetName(_key);
		pObject->Load(_path);

		mObjMap[_key] = pObject;

		return pObject;
	}
	template<typename T>
	inline bool Resources::Add(const wstring& _key, shared_ptr<T> _pObject)
	{
		ObjectType eObjType = GetObjectType<T>();
		KeyObjMap& mObjMap = mResources[static_cast<int>(eObjType)];

		auto findIt = mObjMap.find(_key);
		if (mObjMap.end() != findIt)
			return false;

		mObjMap[_key] = _pObject;
		return true;
	}
	template<typename T>
	inline shared_ptr<T> Resources::Get(const wstring& _key)
	{
		ObjectType eObjType = GetObjectType<T>();
		KeyObjMap& mObjMap = mResources[static_cast<int>(eObjType)];

		auto findIt = mObjMap.find(_key);
		if (mObjMap.end() != findIt)
			return static_pointer_cast<T>(findIt->second);

		return nullptr;
	}
	template<typename T>
	inline ObjectType Resources::GetObjectType()
	{
		if (std::is_same_v<T, GameObject>)
			return ObjectType::GameObject;
		else if (std::is_same_v<T, Texture>)
			return ObjectType::Texture;
		else if (std::is_same_v<T, Shader>)
			return ObjectType::Shader;
		else if (std::is_same_v<T, Material>)
			return ObjectType::Material;
		else if (std::is_same_v<T, Component>)
			return ObjectType::Component;
		else if (std::is_same_v<T, Mesh>)
			return ObjectType::Mesh;
		else if (std::is_same_v<T, MeshData>)
			return ObjectType::MeshData;
		else
		{
			AssertEx(false, L"잘못된 리소스 타입 전달");
			return ObjectType::End;
		}
	}
}




