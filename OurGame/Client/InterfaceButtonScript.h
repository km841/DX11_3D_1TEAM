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

		void SetHoveredCallback(std::function<void()> _callback) { mHoveredCallback = _callback; }
		void SetClickedCallback(std::function<void()> _callback) { mClickedCallback = _callback; }

		void SetHoveredTexture(shared_ptr<Texture> _pTexture) { mpHoveredTexture = _pTexture; }
		void SetNonHoveredTexture(shared_ptr<Texture> _pTexture) { mpNonHoveredTexture = _pTexture; }
		void SetClickedTexture(shared_ptr<Texture> _pTexture) { mpClickedTexture = _pTexture; }

	private:
		bool mbHovered;
		bool mbClicked;

		std::function<void()> mHoveredCallback;
		std::function<void()> mClickedCallback;

		shared_ptr<Texture> mpHoveredTexture;
		shared_ptr<Texture> mpNonHoveredTexture;
		shared_ptr<Texture> mpClickedTexture;
	};
}


