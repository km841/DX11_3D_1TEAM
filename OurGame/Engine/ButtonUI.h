#pragma once
#include "Interface.h"

namespace hm
{
	class ButtonUI :
		public Interface
	{
	public:
		ButtonUI(const string& _name, int _importance, const Vec2& _pos, const Vec2& _scale);
		virtual ~ButtonUI();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Destroy();

	public:
		void SetCallback(std::function<void()> _callback) { mCallback = _callback; }
		void SetClickedColor(const Vec4& _clickedColor) { mClickedColor = _clickedColor; }
		void SetHoveredColor(const Vec4& _hoveredColor) { mHoveredColor = _hoveredColor; }

	private:
		std::function<void()> mCallback;
		Vec4 mClickedColor = Vec4(0.f, 0.f, 0.f, 1.f);
		Vec4 mHoveredColor = Vec4(0.f, 0.f, 0.f, 1.f);

	};
}


