#pragma once
#include "InterfaceFont.h"
namespace hm
{
	struct InterfaceInfo
	{
		InterfaceInfo() {}
		InterfaceInfo(InterfaceType _type, const string& _name, int _imp) 
			: eType(_type), name(_name), importance(_imp) 
		{}

		bool operator> (const InterfaceInfo& _otherInfo) const
		{
			return importance > _otherInfo.importance;
		}

		bool operator< (const InterfaceInfo& _otherInfo) const
		{
			return importance < _otherInfo.importance;
		}

		InterfaceType eType;
		string name;
		int		importance;
	};

	class Interface
	{
	public:
		Interface(const InterfaceInfo& _info);
		virtual ~Interface();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Destroy();

	public:
		void SetInterfaceImportance(int _imp) { mInfo.importance = _imp; }
		int  GetInterfaceImportance() { return mInfo.importance; }

		InterfaceType GetInterfaceType() { return mInfo.eType; }
		InterfaceInfo& GetInterfaceInfo() { return mInfo; }

		const string& GetName() { return mInfo.name; }

		void SetPosition(const Vec2& _pos) { mPos = _pos; }
		const Vec2& GetPosition() { return mPos; }

		void SetScale(const Vec2& _scale) { mScale = _scale; }
		const Vec2& GetScale() { return mScale; }

		void AddChild(Interface* _pChild);
		Interface* GetChild(const string& _name);
		void ChildUpdate();

		void SetColor(const Vec4& _color) { mColor = _color; }
		void SetAlpha(float _alpha) { mColor.w = _alpha; }

		/* Child와 자신을 활성화 */
		void Enable();

		/* Child와 자신을 비활성화 */
		void Disable();

		bool IsEnable() { return mbEnable; }


	protected:
		InterfaceInfo mInfo;
		Vec2 mPos;
		Vec2 mScale;
		bool mbEnable;

		Vec4 mColor;

		std::map<int, Interface*> mChildren;
	};
}


