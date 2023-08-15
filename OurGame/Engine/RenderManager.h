#pragma once
#include "InstancingBuffer.h"

struct BlurInfo
{
	
};

namespace hm
{
	class Texture;
	class Material;
	class Mesh;
	class Scene;
	class Camera;
	class GameObject;
	class ImageFilter;

	class RenderManager
	{
		DECLARE_SINGLE(RenderManager);
	public:
		void Initialize();
		void Render(Scene* _pScene);
		
		void ClearInstancingBuffer();
		void Clear();
		void ClearRenderTargets();

	public:
		void SortGameObject(Scene* _pScene);
		void RenderForward(Scene* _pScene);
		void RenderDeferred(Scene* _pScene);
		void RenderLight(Scene* _pScene);
		void RenderLightBlend();
		void RenderFinal();
		void PushLightData(Scene* _pScene);

		void PostProcessing();

	private:
		void DownScale();
		void Blur();
		void Bloom();

	private:
		void AddParam(UINT64 _instanceID, InstancingParams& _params);
		void RenderInstancing(Camera* _pCamera, const std::vector<GameObject*> _gameObjects);

		void PostProcessInit();

	private:
		UINT32 mWidth;
		UINT32 mHeight;

		// Bloom
		shared_ptr<ImageFilter> mpCopyFilter;
		shared_ptr<ImageFilter> mpSamplingFilter;
		shared_ptr<ImageFilter> mpBlurXFilter;
		shared_ptr<ImageFilter> mpBlurYFilter;
		shared_ptr<ImageFilter> mpCombineFilter;

		ComPtr<ID3D11Buffer>			  mpDownScaleBuffer;	    // 휘도값을 계산할 때 중간값을 저장할 버퍼
		ComPtr<ID3D11UnorderedAccessView> mpDownScaleUAV;			// 순서 없는 접근 뷰
		ComPtr<ID3D11ShaderResourceView>  mpDownScaleSRV;			// 셰이더 리소스 뷰

		ComPtr<ID3D11Buffer>			  mpAvgLumBuffer;			// 평균 휘도 값을 저장할 버퍼
		ComPtr<ID3D11UnorderedAccessView> mpAvgLumUAV;				// 순서 없는 접근 뷰
		ComPtr<ID3D11ShaderResourceView>  mpAvgLumSRV;				// 셰이더 리소스 뷰

		ComPtr<ID3D11Buffer> mpPrevAdaptionBuffer;			// 다음 프레임의 직전 평균 휘도값을 저장할 버퍼
		ComPtr<ID3D11UnorderedAccessView> mpPrevAdaptionUAV;
		ComPtr<ID3D11ShaderResourceView> mpPrevAdaptionSRV;

		ComPtr<ID3D11Texture2D> mpDownScaleSceneRT;		// 다운 스케일된 HDR 텍스처
		ComPtr<ID3D11UnorderedAccessView> mpDownScaleSceneUAV;
		ComPtr<ID3D11ShaderResourceView> mpDownScaleSceneSRV;

		ComPtr<ID3D11Texture2D> mpTempRT[2];				// 임시 텍스처 (영역)
		ComPtr<ID3D11UnorderedAccessView> mpTempUAV[2];
		ComPtr<ID3D11ShaderResourceView> mpTempSRV[2];

		ComPtr<ID3D11Texture2D> mpBloomRT;
		ComPtr<ID3D11UnorderedAccessView> mpBloomUAV;
		ComPtr<ID3D11ShaderResourceView> mpBloomSRV;

		shared_ptr<Material> mpDownScaleFirstPassMaterial; // DownScale Shader + CBuffer
		shared_ptr<Material> mpDownScaleSecondPassMaterial; // DownScale Shader + CBuffer
		shared_ptr<Material> mpBritePassMaterial;
		shared_ptr<Material> mpVerticalBlurMaterial;
		shared_ptr<Material> mpHorizonBlurMaterial;

		std::map<UINT64, InstancingBuffer*> mBuffers;
		
	};

}

