#pragma once
#include "EnginePch.h"
#include "GraphicsCore.h"
#include "SwapChain.h"
#include "ConstantBuffer.h"
#include "MultiRenderTarget.h"
#include "Physics.h"
#include "Font.h"
#include "Tool.h"

namespace hm
{
	class GraphicsCore;
	
	/*
	 - 게임의 중추적인 부분을 담당하는 엔진 클래스
	*/
	class Engine
	{
	public:
		Engine() = default;
		~Engine();

		// 윈도우와 각종 싱글톤 클래스 초기화
		void Initialize(const WindowInfo& _windowInfo);

		// 각종 싱글턴 클래스의 업데이트 함수 호출
		void Update();

		// 씬 및 각종 후처리 기법들 수행
		void Render();

		// 씬을 렌더링하기 전 뷰포트 초기화
		void RenderBegin();

		// Present와 렌더링 후에 처리해야 할 작업들을 처리하는 함수
		void RenderEnd();

		// 프로그램이 종료되기 전 수동으로 정리하는 함수
		void Destroy();

		const WindowInfo& GetWindowInfo() { return mWindowInfo; }
		HWND GetHwnd()		 { return mWindowInfo.hwnd; }
		Vec2 GetResolution() { return Vec2(static_cast<float>(mWindowInfo.width), 
										   static_cast<float>(mWindowInfo.height)); }

		// 엔진이 보유한 클래스를 외부에서 접근할 수 있도록 한다.
		GraphicsCore* GetGraphicsCore() { return mpGraphicsCore; }
		SwapChain*    GetSwapChain()    { return mpSwapChain; }
		ConstantBuffer* GetConstantBuffer(ConstantBufferType _eContantBufferType) { return mConstantBufferGroup[static_cast<int>(_eContantBufferType)]; }
		MultiRenderTarget* GetMultiRenderTarget(MultiRenderTargetType _eMultiRenderTargetType) { return mMultiRenderTargets[static_cast<int>(_eMultiRenderTargetType)]; }
		Physics* GetPhysics() { return mpPhysics; }
		Font* GetFont() { return mpFont; }
		Tool* GetTool() { return mpTool; }

		// 윈도우 사이즈 변경하는 함수
		void ResizeWindow(int _width, int _height);
		void CreateMultiRenderTarget();
		void CreateConstantBuffer(RegisterCBV _eRegister, int _size);

		void SetSwapChainRTVClearColor(Vec4 _color);

	private:
		WindowInfo				mWindowInfo;
		D3D11_VIEWPORT			mViewport;
		D3D11_RECT				mScissorRect;

		GraphicsCore* mpGraphicsCore;
		SwapChain*    mpSwapChain;
		Physics* mpPhysics;
		Font* mpFont;
		Tool* mpTool;

		std::array<ConstantBuffer*, CONSTANT_BUFFER_TYPE_COUNT> mConstantBufferGroup;
		std::array<MultiRenderTarget*, MULTI_RENDER_TARGET_TYPE_COUNT> mMultiRenderTargets;
	};
}
