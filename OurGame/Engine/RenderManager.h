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
		void RenderFinal(Scene* _pScene);
		void PushLightData(Scene* _pScene);

		void PostProcessing();

	private:
		void Blur();
		void Bloom();

	private:
		void AddParam(UINT64 _instanceID, InstancingParams& _params);
		void RenderInstancing(Camera* _pCamera, const std::vector<GameObject*> _gameObjects);

	private:
		UINT32 mWidth;
		UINT32 mHeight;

		// Bloom
		shared_ptr<ImageFilter> mpCopyFilter;
		shared_ptr<ImageFilter> mpSamplingFilter;
		shared_ptr<ImageFilter> mpBlurXFilter;
		shared_ptr<ImageFilter> mpBlurYFilter;
		shared_ptr<ImageFilter> mpCombineFilter;

		std::map<UINT64, InstancingBuffer*> mBuffers;
		
	};

}

