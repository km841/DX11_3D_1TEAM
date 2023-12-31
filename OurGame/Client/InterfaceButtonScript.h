#pragma once
#include "MonoBehavior.h"

namespace hm
{
	class InterfaceButtonScript :
		public MonoBehavior
	{
	public:
		InterfaceButtonScript();
		~InterfaceButtonScript() = default;

		virtual void FixedUpdate() override;
		virtual Component* Clone(GameObject* _pGameObject) override;

		void SetNonHoveredCallback(std::function<void()> _callback) { mNonHoveredCallback = _callback; }
		void SetHoveredCallback(std::function<void()> _callback) { mHoveredCallback = _callback; }
		void SetClickedCallback(std::function<void()> _callback) { mClickedCallback = _callback; }

		std::function<void()> GetNonHoveredCallback() { return mNonHoveredCallback; }
		std::function<void()> GetHoveredCallback() { return mHoveredCallback; }
		std::function<void()> GetClickedCallback() { return mClickedCallback; }
		
		void SetHoveredTexture(shared_ptr<Texture> _pTexture) { mpHoveredTexture = _pTexture; }
		void SetNonHoveredTexture(shared_ptr<Texture> _pTexture) { mpNonHoveredTexture = _pTexture; }
		void SetClickedTexture(shared_ptr<Texture> _pTexture) { mpClickedTexture = _pTexture; }

	private:
		bool mbHovered;
		bool mbClicked;

		std::function<void()> mNonHoveredCallback;
		std::function<void()> mHoveredCallback;
		std::function<void()> mClickedCallback;

		shared_ptr<Texture> mpHoveredTexture;
		shared_ptr<Texture> mpNonHoveredTexture;
		shared_ptr<Texture> mpClickedTexture;
	};
}


