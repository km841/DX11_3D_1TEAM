#pragma once
#include "Component.h"
#include "Frustum.h"

namespace hm
{
    class Shader;
    enum class ProjectionType
    {
        Orthographic,
        Perspective,
    };

	class Camera :
		public Component
	{
    public:
        Camera();
        virtual ~Camera();

        virtual Component* Clone(GameObject* _pGameObject);

        virtual void    Update() override;

        /* 뷰행렬, 투영행렬을 계산한다.*/
        virtual void    FinalUpdate() override;

        void            SetProjectionType(ProjectionType eType) { meProjectionType = eType; }
        ProjectionType  GetProjectionType()   const { return meProjectionType; }

        void            SetCullingMask(LayerType _eLayerType, bool _bFlag);
        void            DisableAllCullingMask();
        void            EnableAllCullingMask();

        const Matrix& GetViewMatrix()       const { return mMatView; }
        const Matrix& GetOldViewMatrix()    const { return mMatOldView; }
        const Matrix& GetProjectionMatrix() const { return mMatProjection; }

        void SetWidth(float _width) { mWidth = _width; }
        void SetHeight(float _height) { mHeight = _height; }
        void SetScale(float _scale) { mScale = _scale; }
        void SetFar(float _far) { mFar = _far; }
        void SetFov(float _fov) { mFov = _fov; }

    public:
        void SortGameObject();
        void SortStaticShadowObject();
        void SortDynamicShadowObject();

        /* Forward Rendering으로 그려질 물체들을 그려주는 함수 */
        void RenderForward();

        void RenderDeferred();

        void RenderParticle();

        void RenderShadow();

        void RenderEffect();

        void RenderReflect(shared_ptr<Shader> _pShader);

        std::vector<GameObject*>&       GetForwardObjectsRef() { return mForwardObjects; }
        const std::vector<GameObject*>& GetForwardObjects() { return mForwardObjects; }
        const std::vector<GameObject*>& GetDeferredObjects() { return mDeferredObjects; }
        const std::vector<GameObject*>& GetEffectObjects() { return mEffectObjects; }
        const std::vector<GameObject*>& GetReflectObject() { return mReflectObjects; }

        void ZSortGroup(std::vector<GameObject*>& _gameObjects) { std::sort(_gameObjects.begin(), _gameObjects.end(), ZSort); }
        static bool ZSort(GameObject* _pFirst, GameObject* _pSecond);

	private:
        ProjectionType meProjectionType;

        float           mNear;
        float           mFar;
        float           mFov;
        float           mScale;
        UINT32          mCullingMask;
        Matrix          mMatView;
        Matrix          mMatOldView;
        Matrix          mMatProjection;

        float           mWidth;
        float           mHeight;

        std::vector<GameObject*> mForwardObjects;
        std::vector<GameObject*> mDeferredObjects;
        std::vector<GameObject*> mParticleObjects;
        std::vector<GameObject*> mShadowObjects;
        std::vector<GameObject*> mEffectObjects;
        std::vector<GameObject*> mReflectObjects;

        Frustum         mFrustumCulling;
	};
}

