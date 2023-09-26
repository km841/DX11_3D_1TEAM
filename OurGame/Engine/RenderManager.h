#pragma once
#include "InstancingBuffer.h"

struct BlurInfo
{
	
};

namespace hm
{
	class StructuredBuffer;
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
		void RenderEffect(Scene* _pScene);
		void RenderLight(Scene* _pScene);
		void RenderShadow(Scene* _pScene);
		void RenderStaticShadow(Scene* _pScene);
		void RenderDynamicShadow(Scene* _pScene);
		void RenderRimLighting();
		void RenderLightBlend();
		void RenderBloom();
		void RenderFinal();
		void RenderScreenEffect();
		void PushLightData(Scene* _pScene);

		void UpdateScreenEffect();
		void ComputeScreenEffect(ScreenEffectInfo* _effectInfo, int _groupIndex);

		void PostProcessing();
		void BakeStaticShadow(Scene* _pScene);

	public:
		void SetPostProcessing(bool _bFlag);
		bool IsApplyPostProcessing() { return mbEnablePostProcessing; }

		void SetHDR(bool _bFlag);
		bool IsApplyHDR()			 { return mbEnableHDR; }

		void SetRimLighting(bool _bFlag);
		bool IsApplyRimLighting()    { return mbEnableRim; }

		void SetDebugMode(bool _bFlag) { mbDebugMode = _bFlag; }
		bool IsDebugMode()			   { return mbDebugMode; }

		void AddScreenEffect(ScreenEffectInfo* _effectInfo, int _groupIndex = 0);
		void AddFadeEffect(ScreenEffectType _eType, float _endTime, std::function<void()> _startCallback = nullptr, std::function<void()> _endCallback = nullptr, const Vec4& _color = Vec4::Zero, int _groupIndex = 0);
		void AddHoldEffect(float _endTime, std::function<void()> _startCallback = nullptr, std::function<void()> _endCallback = nullptr, const Vec4& _color = Vec4::Zero, int _groupIndex = 0);
		void RemoveCurrentEffect(int _groupIndex = 0);
		void RemoveGroupEffect(int _groupIndex = 0);
		void RemoveAllEffect();

	private:
		void DownScale();
		void Blur();
		void Bloom();
		void ComputeBloom();
		void ComputeBlur();
		void ToneMapping();

		void ComputeLight();
		void ComputeHDR();
		void ComputeSSAO();

	private:
		void AddParam(UINT64 _instanceID, InstancingParams& _params);
		void RenderInstancing(Camera* _pCamera, const std::vector<GameObject*> _gameObjects);

		void PostProcessInit();

	private:
		// Bloom
		shared_ptr<ImageFilter> mpCopyFilter;
		shared_ptr<ImageFilter> mpSamplingFilter;
		shared_ptr<ImageFilter> mpBlurXFilter;
		shared_ptr<ImageFilter> mpBlurYFilter;
		shared_ptr<ImageFilter> mpCombineFilter;

		shared_ptr<StructuredBuffer> mpDownScaleBuffer;    // 휘도값 계산 시 중간값 저장하는 버퍼
		shared_ptr<StructuredBuffer> mpAvgLumBuffer;       // 평균 휘도값 저장하는 버퍼
		shared_ptr<StructuredBuffer> mpPrevAdaptionBuffer; // 다음 프레임 직전 휘도값을 저장하는 버퍼
		
		shared_ptr<Texture> mpDownScaleSceneTexture;       // 다운 스케일된 HDR 텍스쳐
		shared_ptr<Texture> mpBloomTexture;
		shared_ptr<Texture> mpTempFirstTexture;
		shared_ptr<Texture> mpTempSecondTexture;

		shared_ptr<Material> mpDownScaleFirstPassMaterial; // DownScale Shader + CBuffer
		shared_ptr<Material> mpDownScaleSecondPassMaterial; // DownScale Shader + CBuffer
		shared_ptr<Material> mpBritePassMaterial;
		shared_ptr<Material> mpVerticalBlurMaterial;
		shared_ptr<Material> mpHorizonBlurMaterial;
		shared_ptr<Material> mpHDRMaterial;

		shared_ptr<Material> mpDownScaleMaterial;
		shared_ptr<Texture> mpBlurXTexture;
		shared_ptr<Texture> mpBlurYTexture;

		std::array<std::queue<ScreenEffectInfo*>, SCREEN_EFFECT_GROUP_COUNT> mScreenEffectGroup;
		std::array<ScreenEffectInfo*, SCREEN_EFFECT_GROUP_COUNT> mActiveEffect;

		float mDOFFarStart;
		float mDOFFarRange;
		float mBloomThreshold;
		float mBloomScale;

		UINT32 mWidth;
		UINT32 mHeight;
		UINT32 mDomain;
		UINT32 mDownScaleGroups;
		float mAdatation;

		float mMiddleGrey;
		float mWhite;

		bool mbEnablePostProcessing;
		bool mbEnableHDR;
		bool mbEnableRim;
		bool mbDebugMode;

		std::map<UINT64, InstancingBuffer*> mBuffers;
		
	};

}

