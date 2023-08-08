#pragma once
/* SwapChain을 관리해주는 클래스
* Back Buffer 생성 
* 생성된 BackBuffer를 이용해서 RenderTarget View 생성
*/
namespace hm
{
	class SwapChain
	{
	public:
		// 내부적으로 CreateSwapChain과 CreateRTV 함수를 호출해준다.
		void Initialize();

		// 백버퍼에 그려진 물체들을 화면에 뿌려주는 함수
		void Present();

		ComPtr<IDXGISwapChain> GetSwapChain() { return mpSwapChain; }

	private:
		// SwapChain 생성
		void CreateSwapChain();

		// BackBuffer를 이용하여 RenderTarget View 생성
		void CreateRTV();

	private:
		ComPtr<IDXGISwapChain>		   mpSwapChain;
		ComPtr<ID3D11RenderTargetView> mpRTV;
	};
}


