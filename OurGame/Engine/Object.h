#pragma once
/*
* 씬을 이루는 모든 오브젝트들의 부모 클래스
*/

namespace hm
{
	class Object
	{

	public:
		Object(ObjectType _eObjectType);
		virtual ~Object();
		virtual void Destroy() { }

	public:
		void SetName(const wstring& _name) { mName = _name; }
		const wstring& GetName() { return mName; }
		ObjectType GetType() { return meObjectType; }
		UINT32 GetID() { return mID; }

	public:
		friend class Resources;
		virtual void Load(const wstring& _path) { }
		virtual void Save(const wstring& _path) { }
		virtual void Save(FILE* _pFile) { }
		virtual void Load(FILE* _pFile) { }

	protected:
		wstring mName;
		ObjectType meObjectType;
		UINT32 mID;
	};
}


