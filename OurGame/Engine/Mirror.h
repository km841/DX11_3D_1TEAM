#pragma once
#include "Component.h"

namespace hm
{
    using SimpleMath::Plane;
    class Camera;
	class Mirror :
		public Component
	{
    public:
        Mirror();
        virtual ~Mirror();

    public:
        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FinalUpdate() override;
        virtual void Render() override;

        virtual Component* Clone(GameObject* _pGameObject);

    public:
        const Matrix& GetReflectMatrix() { return mReflectMatrix; }
        void RenderMasking(Camera* _pCamera);
        void RenderReflect(Camera* _pCamera);

    private:
        void CreateReflectPlane();


    private:
        Plane mReflectPlane;
        Matrix mReflectMatrix;

	};
}


