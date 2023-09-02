#pragma once
#include "Component.h"

namespace hm
{
    class Mesh;
    class Material;
    class Camera;

    enum class LightType
    {
        DirectionalLight,
        PointLight,
        SpotLight,
    };

    struct LightColor
    {
        Vec4 diffuse = {};
        Vec4 ambient = {};
        Vec4 specular = {};
    };

    struct LightInfo
    {
        LightColor color = {};
        Vec4 position = {};
        Vec4 direction = {};
        __int32 eLightType = {};
        float range = {};
        float angle = {};
        __int32 padding = {};
    };

    struct LightParams
    {
        __int32 lightCount= 0;
        Vec3 padding = {};
        LightInfo lights[50] = {};
    };

	class Light :
		public Component
	{
    public:
        Light();
        virtual ~Light();

        virtual void FinalUpdate() override;
        void Render(Camera* _pCamera);

        virtual Component* Clone(GameObject* _pGameObject);

    public:
        void RenderShadow();

        const LightInfo& GetLightInfo() { return mLightInfo; }
        void SetLightDirection(Vec3 _direction);

        Vec3 GetDiffuse() { return Vec3(mLightInfo.color.diffuse.x, mLightInfo.color.diffuse.y, mLightInfo.color.diffuse.z); }
        Vec3 GetAmbient() { return Vec3(mLightInfo.color.ambient.x, mLightInfo.color.ambient.y, mLightInfo.color.ambient.z); }
        float GetRange() { return mLightInfo.range; }

        void AddDiffuse(const Vec3& _diffuse) { mLightInfo.color.diffuse += _diffuse; }
        void SetDiffuse(const Vec3& _diffuse) { mLightInfo.color.diffuse = _diffuse; }
        void SetAmbient(const Vec3& _ambient) { mLightInfo.color.ambient = _ambient; }
        void SetSpecular(const Vec3& _specular) { mLightInfo.color.specular = _specular; }

        void SetLightType(LightType _eLightType);
        void SetLightRange(float _range) { mLightInfo.range = _range; }
        void SetLightAngle(float _angle) { mLightInfo.angle = _angle; }
        void SetLightIndex(int _index) { mLightIndex = _index; }

        LightType GetLightType() { return static_cast<LightType>(mLightInfo.eLightType); }

    private:
        LightInfo mLightInfo;
        int mLightIndex;
        shared_ptr<Mesh> mpMesh;
        shared_ptr<Material> mpMaterial;

        GameObject* mpShadowCamera;
	};

}

