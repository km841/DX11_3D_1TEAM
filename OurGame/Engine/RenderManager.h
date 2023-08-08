#pragma once
#include "InstancingBuffer.h"
namespace hm
{
	class Scene;
	class Camera;
	class GameObject;
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
		void PostProcessing(Scene* _pScene);
		void PushLightData(Scene* _pScene);

	private:
		void AddParam(UINT64 _instanceID, InstancingParams& _params);
		void RenderInstancing(Camera* _pCamera, const std::vector<GameObject*> _gameObjects);

	private:
		std::map<UINT64, InstancingBuffer*> mBuffers;
	};

}

