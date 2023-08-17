#pragma once
#include "Object.h"
#include "Shader.h"

namespace hm
{
    class Shader;
    class Texture;

    struct MaterialSubset
    {
        std::array<shared_ptr<Texture>, TEXTURE_VALUE_COUNT> textures;
        MaterialParams materialParams;
        wstring name;

        void SetTexture(int _index, shared_ptr<Texture> _pTexture) 
        { 
            textures[_index] = _pTexture;
            materialParams.SetTexOn(_index, nullptr != _pTexture ? 1 : 0);
        }
    };

    struct MaterialContainer
    {
        std::vector<MaterialSubset*> materialSubsetVec;
        void AddSubset(MaterialSubset* _pSubset) { materialSubsetVec.push_back(_pSubset); }
    };

	class Material :
		public Object
	{
    public:
        Material();
        virtual ~Material();

        /* 그래픽 작업에 필요한 여러 작업을 처리한다.
        * Material에 저장된 데이터들을 Material용도의 ConstantBuffer에 밀어넣는다.
        * 현재 가진 Texture들을 GPU에 매핑한다.
        * 멤버 변수인 Shader의 Update를 실행한다.
        */
        void ClearGraphicData();
        void PushGraphicData(int _containerIndex = 0, int _subsetIndex = 0);
        void PushGraphicDataExceptForTextures(int _containerIndex = 0, int _subsetIndex = 0);
        void PushComputeData();
        void Dispatch(UINT32 _countX, UINT32 _countY, UINT32 _countZ);
        void SetSamplerType(SamplerType _eSamplerType) { mpShader->SetSamplerType(_eSamplerType); }

        void                SetShader(shared_ptr<Shader> _pShader) { mpShader = _pShader; }
        shared_ptr<Shader>  GetShader() { return mpShader; }
        shared_ptr<Texture> GetTexture(int _index, int _containerIndex = 0, int _subsetIndex = 0) { return mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->textures[_index]; }
        void                SetTexture(int _index, shared_ptr<Texture> _pTexture, int _containerIndex = 0, int _subsetIndex = 0);
        void                SetTextureAllSubset(int _index, shared_ptr<Texture> _pTexture);

        MaterialSubset* GetMaterialSubset(int _containerIndex, int _subsetindex) { return mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetindex]; }
        MaterialContainer* GetMaterialContainer(int _containerIndex) { return mMaterialContainerVec[_containerIndex]; }

        //void SetUAV(int _index, shared_ptr<Texture> pTexture);

        void SetInt(int _index, int _value, int _containerIndex = 0, int _subsetIndex = 0);
        void SetIntAllSubset(int _index, int _value);

        void SetFloat(int _index, float _value, int _containerIndex = 0, int _subsetIndex = 0);
        void SetFloatAllSubset(int _index, float _value);

        void SetVec2(int _index, Vec2 _value, int _containerIndex = 0, int _subsetIndex = 0);
        void SetVec3(int _index, Vec3 _value, int _containerIndex = 0, int _subsetIndex = 0);
        void SetVec4(int _index, Vec4 _value, int _containerIndex = 0, int _subsetIndex = 0);

        shared_ptr<Material> Clone();
        void ClearComputeData();

        void AddMaterialContainer(MaterialContainer* _pMaterialContainer);
        UINT32 GetMaterialContainerCount() { return static_cast<UINT32>(mMaterialContainerVec.size()); }
        UINT32 GetMaterialContainerSubsetCount(int _containerIndex) { return static_cast<UINT32>(mMaterialContainerVec[_containerIndex]->materialSubsetVec.size()); }
        void ClearMaterialContainers();

    private:
        std::vector<MaterialContainer*> mMaterialContainerVec;

        shared_ptr<Shader>      mpShader;
        void** mppNullptr;
	};
}


