#pragma once
namespace hm
{
	class GameObject;
	class Tool
	{
	public:
		Tool();
		~Tool();
	public:
		void Initialize(HWND _hwnd, ComPtr<ID3D11Device> _pDevice, ComPtr<ID3D11DeviceContext> _pContext);
		void Update();
		void Render();

	public:
		LRESULT DispatchWndMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		void SetGameObject(GameObject* _pGameObject);
		const Vec3& GetSnaps() { return mSnaps; }

		void UseGizmo() { InitGizmoGui();  mbUseGizmo = true; }
		void UseAnimTool() { InitAnimGui(); mbUseAnimGui = true; }

	private:
		void InitGui();

		void InitGizmoGui();
		void UpdateGizmo();
		void EditTransform();

		void EditScaleFromKeyboard(Matrix& _mat);
		void EditTranslationFromKeyboard(Matrix& _mat);

		void ShowTransform();

	private:
		void InitAnimGui();
		void UpdateAnimation();

	private:
		HWND mHwnd;
		ComPtr<ID3D11Device> mpDevice;
		ComPtr<ID3D11DeviceContext> mpContext;
		GameObject* mpGameObject;

		Vec3 mSnaps;

		ImGuizmo::OPERATION meCurrentOperation;
		ImGuizmo::MODE meCurrentMode;

		std::list<Matrix> mUndoStack;
		std::list<Matrix> mRedoStack;

		bool mbUseGizmo;
		bool mbUseAnimGui;
	};
}


