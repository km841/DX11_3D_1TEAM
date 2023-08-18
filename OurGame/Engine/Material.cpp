#include "pch.h"
#include "Material.h"
#include "Engine.h"
#include "Texture.h"

namespace hm
{
	Material::Material()
		: Object(ObjectType::Material)
		, mppNullptr(nullptr)
	{
		if (mMaterialContainerVec.empty())
		{
			AddMaterialContainer(new MaterialContainer);
			GetMaterialContainer(0)->AddSubset(new MaterialSubset);
		}
	}

	Material::~Material()
	{
		ClearMaterialContainers();
	}

	void Material::ClearGraphicData()
	{
		for (int i = 0; i < MATERIAL_VALUE_COUNT; ++i)
		{
			CONTEXT->PSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
				reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));

			CONTEXT->GSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
				reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));

			CONTEXT->CSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
				reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));

			CONTEXT->VSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
				reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));

			CONTEXT->DSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
				reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));

			CONTEXT->HSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
				reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));
		}
	}

	void Material::PushGraphicData(int _containerindex, int _subsetIndex)
	{
		CONST_BUFFER(ConstantBufferType::Material)->PushData(&mMaterialContainerVec[_containerindex]->materialSubsetVec[_subsetIndex]->materialParams, sizeof(MaterialParams));
		mpShader->Update();

		for (int i = 0; i < TEXTURE_VALUE_COUNT; ++i)
		{
			if (nullptr == mMaterialContainerVec[_containerindex]->materialSubsetVec[_subsetIndex]->textures[i])
			{
				CONTEXT->PSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));

				CONTEXT->GSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));

				CONTEXT->CSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));

				CONTEXT->VSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));

				CONTEXT->DSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));

				CONTEXT->HSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));
			}

			else
			{
				CONTEXT->PSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					mMaterialContainerVec[_containerindex]->materialSubsetVec[_subsetIndex]->textures[i]->GetSRV().GetAddressOf());

				CONTEXT->GSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					mMaterialContainerVec[_containerindex]->materialSubsetVec[_subsetIndex]->textures[i]->GetSRV().GetAddressOf());

				CONTEXT->CSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					mMaterialContainerVec[_containerindex]->materialSubsetVec[_subsetIndex]->textures[i]->GetSRV().GetAddressOf());

				CONTEXT->VSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					mMaterialContainerVec[_containerindex]->materialSubsetVec[_subsetIndex]->textures[i]->GetSRV().GetAddressOf());

				CONTEXT->DSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					mMaterialContainerVec[_containerindex]->materialSubsetVec[_subsetIndex]->textures[i]->GetSRV().GetAddressOf());

				CONTEXT->HSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					mMaterialContainerVec[_containerindex]->materialSubsetVec[_subsetIndex]->textures[i]->GetSRV().GetAddressOf());
			}

		}
	}

	void Material::PushGraphicDataExceptForTextures(int _containerIndex, int _subsetIndex)
	{
		CONST_BUFFER(ConstantBufferType::Material)->PushData(&mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->materialParams, sizeof(MaterialParams));
		mpShader->Update();
	}


	void Material::PushComputeData()
	{
		CONST_BUFFER(ConstantBufferType::Material)->PushData(&mMaterialContainerVec[0]->materialSubsetVec[0]->materialParams, sizeof(MaterialParams));
		CONST_BUFFER(ConstantBufferType::Material)->Mapping();
		mpShader->Update();

		//for (int i = 0; i < TEXTURE_VALUE_COUNT; ++i)
		//{
		//	if (nullptr == mMaterialContainerVec[0]->materialSubsetVec[0]->textures[i])
		//	{
		//		//CONTEXT->CSSetUnorderedAccessViews(static_cast<int>(RegisterUAV::u0) + i, 1,
		//		//	reinterpret_cast<ID3D11UnorderedAccessView**>(&mppNullptr), 0);

		//		//CONTEXT->CSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
		//		//	reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));
		//	}

		//	else
		//	{
		//		CONTEXT->CSSetUnorderedAccessViews(static_cast<int>(RegisterUAV::u0) + i, 1,
		//			mMaterialContainerVec[0]->materialSubsetVec[0]->textures[i]->GetUAV().GetAddressOf(), 0);

		//		CONTEXT->CSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
		//			mMaterialContainerVec[0]->materialSubsetVec[0]->textures[i]->GetSRV().GetAddressOf());
		//	}
		//}
	}

	void Material::Dispatch(UINT32 _countX, UINT32 _countY, UINT32 _countZ)
	{
		PushComputeData();
		CONTEXT->Dispatch(_countX, _countY, _countZ);
		ClearComputeData();
	}

	void Material::SetTexture(int _index, shared_ptr<Texture> _pTexture, int _containerIndex, int _subsetIndex)
	{
		mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->textures[_index] = _pTexture;
		if (nullptr != _pTexture)
		{
			mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->materialParams.SetTexOn(_index, 1);
		}
		else
		{
			mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->materialParams.SetTexOn(_index, 0);
		}
	}

	void Material::SetTextureAllSubset(int _index, shared_ptr<Texture> _pTexture)
	{
		for (int i = 0; i < mMaterialContainerVec.size(); ++i)
		{
			for (int j = 0; j < mMaterialContainerVec[i]->materialSubsetVec.size(); ++j)
			{
				mMaterialContainerVec[i]->materialSubsetVec[j]->SetTexture(_index, _pTexture);
			}
		}
	}

	void Material::SetInt(int _index, int _value, int _containerIndex, int _subsetIndex)
	{
		mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->materialParams.SetInt(_index, _value);
	}

	void Material::SetIntAllSubset(int _index, int _value)
	{
		for (int i = 0; i < mMaterialContainerVec.size(); ++i)
		{
			for (int j = 0; j < mMaterialContainerVec[i]->materialSubsetVec.size(); ++j)
			{
				mMaterialContainerVec[i]->materialSubsetVec[j]->materialParams.SetInt(_index, _value);
			}
		}
	}

	void Material::SetFloat(int _index, float _value, int _containerIndex, int _subsetIndex)
	{
		mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->materialParams.SetFloat(_index, _value);
	}

	void Material::SetFloatAllSubset(int _index, float _value)
	{
		for (int i = 0; i < mMaterialContainerVec.size(); ++i)
		{
			for (int j = 0; j < mMaterialContainerVec[i]->materialSubsetVec.size(); ++j)
			{
				mMaterialContainerVec[i]->materialSubsetVec[j]->materialParams.SetFloat(_index, _value);
			}
		}
	}

	void Material::SetVec2(int _index, Vec2 _value, int _containerIndex, int _subsetIndex)
	{
		mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->materialParams.SetVec2(_index, _value);
	}

	void Material::SetVec3(int _index, Vec3 _value, int _containerIndex, int _subsetIndex)
	{
		mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->materialParams.SetVec3(_index, _value);
	}

	void Material::SetVec3AllSubset(int _index, Vec3 _value)
	{
		for (int i = 0; i < mMaterialContainerVec.size(); ++i)
		{
			for (int j = 0; j < mMaterialContainerVec[i]->materialSubsetVec.size(); ++j)
			{
				mMaterialContainerVec[i]->materialSubsetVec[j]->materialParams.SetVec3(_index, _value);
			}
		}
	}

	void Material::SetVec4(int _index, Vec4 _value, int _containerIndex, int _subsetIndex)
	{
		mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->materialParams.SetVec4(_index, _value);
	}

	void Material::SetColorAllSubset(Vec3 _color)
	{
		SetTextureAllSubset(0, nullptr);
		SetVec3AllSubset(0, _color);
	}

	shared_ptr<Material> Material::Clone()
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();

		for (int i = 0; i < mMaterialContainerVec.size(); ++i)
		{
			pMaterial->AddMaterialContainer(new MaterialContainer);
			MaterialContainer* pContainer = pMaterial->GetMaterialContainer(i);

			for (int j = 0; j < mMaterialContainerVec[i]->materialSubsetVec.size(); ++j)
			{
				pContainer->AddSubset(new MaterialSubset);
				pMaterial->mMaterialContainerVec[i]->materialSubsetVec[j]->materialParams = mMaterialContainerVec[i]->materialSubsetVec[j]->materialParams;
				pMaterial->mMaterialContainerVec[i]->materialSubsetVec[j]->textures = mMaterialContainerVec[i]->materialSubsetVec[j]->textures;
			}
		}

		pMaterial->SetShader(mpShader);
		return pMaterial;
	}

	void Material::ClearComputeData()
	{
		for (int i = 0; i < MATERIAL_VALUE_COUNT; ++i)
		{
			CONTEXT->CSSetUnorderedAccessViews(static_cast<int>(RegisterUAV::u0) + i, 1,
				reinterpret_cast<ID3D11UnorderedAccessView**>(&mppNullptr), 0);

			CONTEXT->CSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
				reinterpret_cast<ID3D11ShaderResourceView**>(&mppNullptr));
		}
	}
	void Material::AddMaterialContainer(MaterialContainer* _pMaterialContainer)
	{
		mMaterialContainerVec.push_back(_pMaterialContainer);
	}
	void Material::ClearMaterialContainers()
	{
		for (int i = 0; i < mMaterialContainerVec.size(); ++i)
		{
			for (int j = 0; j < mMaterialContainerVec[i]->materialSubsetVec.size(); ++j)
			{
				SAFE_DELETE(mMaterialContainerVec[i]->materialSubsetVec[j]);
			}
			mMaterialContainerVec[i]->materialSubsetVec.clear();
			SAFE_DELETE(mMaterialContainerVec[i]);
		}
		mMaterialContainerVec.clear();
	}
}


