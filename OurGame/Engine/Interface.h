#pragma once
#include "GameObject.h"
namespace hm
{
	class Interface : 
		public GameObject
	{
	public:
		Interface();
		virtual ~Interface();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void Enable();
		virtual void Disable();

		void SetAlpha(float _alpha) { mAlphaFunc(_alpha); }
		void SetColor(const Vec3& _color) { mColorFunc(_color); }
		void SetAlphaFunction(std::function<void(float)> _alphaFunc) { mAlphaFunc = _alphaFunc; }
		void SetColorFunction(std::function<void(Vec3)> _colorFunc) { mColorFunc = _colorFunc; }
		void SetText(const wstring& _text, float _size, bool _bIsShadow);
		void SetTextColor(const Vec4& _color);

		void AddChild(Interface* _pChild);
		Interface* GetChild(const wstring& _name);
		void UpdateChild();

	protected:
		std::map<int, Interface*> mChildren;
		std::function<void(float)> mAlphaFunc;
		std::function<void(Vec3)> mColorFunc;
	};
}


