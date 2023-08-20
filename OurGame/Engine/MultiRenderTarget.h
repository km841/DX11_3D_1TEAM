#pragma once
#include "Texture.h"
namespace hm
{
	enum class MultiRenderTargetType
	{
		SwapChain,
		G_Buffer,
		Light,
		RimLighting,
		LightBlend,
		End,
	};

	enum
	{
		MULTI_RENDER_TARGET_TYPE_COUNT = MultiRenderTargetType::End,
		G_BUGGER_GROUP_COUNT = 5,
		SWAP_CHAIN_BUFFER_COUNT = 1,
		LIGHTING_GROUP_COUNT = 2,
		RIM_LIGHTING_GROUP_COUNT = 1,
		LIGHTBLEND_GROUP_COUNT = 1,
	};

	struct RenderTarget
	{
		shared_ptr<Texture> pTarget;
		float clearColors[4];
	};

	/*
	* RenderTarget의 그룹들을 관리하는 클래스
	* 주 목적은 Deferred Rendering을 사용하기 위함
	* OMSetRenderTarget 등의 렌더타겟과 관련된 작업들이 이루어진다.
	*/
	class MultiRenderTarget
	{
	public:
		/* Multi Render Target에 필요한 각 인자를 받아 내부에 저장하는 함수
		* _eRenderTargetType   : 렌더 타겟의 타입 (ex. SwapChain , Light , G-Buffer)
		* _renderTargets       : 외부에서 만들어진 렌더타겟 벡터
		* _depthStencilTexture : 깊이 버퍼 텍스쳐
		*/
		void Create(MultiRenderTargetType _eRenderTargetType, const std::vector<RenderTarget>& _renderTargets, shared_ptr<Texture> _depthStencilTexture);

		/* 다수의 렌더타겟을 세팅하는 함수
		* DeviceContext의 OMSetRenderTarget을 래핑한 함수
		* mRenderTargets를 모두 RenderTarget으로 설정한다
		*/
		void OMSetRenderTarget();

		/* mRenderTargets의 특정 인덱스를 현재 RenderTarget으로 세팅하는 함수
		* _index : 렌더타겟으로 설정할 인덱스
		*/
		void OMSetRenderTarget(int _index);

		/* 자신에게 그려진 것을 모두 지워주는 함수
		* RenderTargetView 뿐만 아니라 DepthStencilView도 초기화한다.
		*/
		void ClearRenderTargetView();

		void SetClearColor(Vec4 _color);
		void SetClearColor(int _index, Vec4 _color);

	private:
		MultiRenderTargetType	     meRenderTargetType;
		std::vector<RenderTarget>	 mRenderTargets;
		int							 mRenderTargetCount;
		shared_ptr<Texture>		     mpDepthStencilTexture;

	};

}

