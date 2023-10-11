#include "pch.h"
#include "Material.h"
#include "Engine.h"
#include "Texture.h"
#include "Resources.h"

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

	void Material::Save(FILE* _pFile)
	{
		AssertEx(nullptr != _pFile, L"Material::Save() - 파일포인터가 nullptr이다");

		wstring shaderName = mpShader->GetName();
		UINT32 shaderNameCount = static_cast<UINT32>(shaderName.size());

		fwrite(&shaderNameCount, sizeof(UINT32), 1, _pFile);
		fwrite(shaderName.c_str(), sizeof(wchar_t), shaderName.size(), _pFile);

		UINT32 mtrlContainerCount = static_cast<UINT32>(mMaterialContainerVec.size());
		fwrite(&mtrlContainerCount, sizeof(UINT32), 1, _pFile);

		for (UINT32 i = 0; i < mtrlContainerCount; ++i)
		{
			MaterialContainer* pMaterialContainer = mMaterialContainerVec[i];
			
			UINT32 subsetCount = static_cast<UINT32>(pMaterialContainer->materialSubsetVec.size());
			fwrite(&subsetCount, sizeof(UINT32), 1, _pFile);

			for (UINT32 j = 0; j < subsetCount; ++j)
			{
				MaterialSubset* pMaterialSubset = pMaterialContainer->materialSubsetVec[j];
				fwrite(&pMaterialSubset->materialParams, sizeof(MaterialParams), 1, _pFile);

				UINT32 textureCount = static_cast<UINT32>(pMaterialSubset->textures.size());
				UINT32 existsTextureCount = 0;

				for (UINT t = 0; t < textureCount; ++t)
					existsTextureCount += nullptr != pMaterialSubset->textures[t] ? 1 : 0;

				fwrite(&existsTextureCount, sizeof(UINT32), 1, _pFile);

				for (UINT32 k = 0; k < textureCount; ++k)
				{
					if (nullptr != pMaterialSubset->textures[k])
					{
						fwrite(&k, sizeof(UINT32), 1, _pFile);
						SaveTexture(_pFile, pMaterialSubset->textures[k]);
					}
				}
			}
		}
	}

	void Material::Load(FILE* _pFile)
	{
		AssertEx(nullptr != _pFile, L"Material::Load() - 파일포인터가 nullptr이다");

		UINT32 shaderNameCount = 0;
		wstring shaderName;

		fread(&shaderNameCount, sizeof(UINT32), 1, _pFile);
		shaderName.resize(shaderNameCount);

		fread(shaderName.data(), sizeof(wchar_t), shaderNameCount, _pFile);
		SetShader(GET_SINGLE(Resources)->Get<Shader>(shaderName));
		
		UINT32 mtrlContainerCount = 0;
		fread(&mtrlContainerCount, sizeof(UINT32), 1, _pFile);

		for (UINT32 i = 0; i < mtrlContainerCount; ++i)
		{
			MaterialContainer* pMaterialContainer = new MaterialContainer;
			mMaterialContainerVec.push_back(pMaterialContainer);

			UINT32 subsetCount = 0;
			fread(&subsetCount, sizeof(UINT32), 1, _pFile);

			for (UINT32 j = 0; j < subsetCount; ++j)
			{
				MaterialSubset* pSubset = new MaterialSubset;
				pMaterialContainer->AddSubset(pSubset);

				fread(&pSubset->materialParams, sizeof(MaterialParams), 1, _pFile);

				UINT32 existsTextureCount = 0;
				fread(&existsTextureCount, sizeof(UINT32), 1, _pFile);

				for (UINT32 k = 0; k < existsTextureCount; ++k)
				{
					UINT32 registerIdx = 0;
					fread(&registerIdx, sizeof(UINT32), 1, _pFile);

					wstring textureKey;
					UINT32 textureKeyCount = 0;
					fread(&textureKeyCount, sizeof(UINT32), 1, _pFile);
					textureKey.resize(textureKeyCount);
					fread(textureKey.data(), sizeof(wchar_t), textureKeyCount, _pFile);

					wstring fullPath;
					UINT32 fullPathCount = 0;
					fread(&fullPathCount, sizeof(UINT32), 1, _pFile);
					fullPath.resize(fullPathCount);
					fread(fullPath.data(), sizeof(wchar_t), fullPathCount, _pFile);

					shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(textureKey, fullPath);
					pSubset->textures[registerIdx] = pTexture;
				}
			}
		}
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
		CONST_BUFFER(ConstantBufferType::Bloom)->PushData(&mMaterialContainerVec[_containerindex]->materialSubsetVec[_subsetIndex]->bloomParams, sizeof(BloomParams));
		
		CONST_BUFFER(ConstantBufferType::Material)->Mapping();
		CONST_BUFFER(ConstantBufferType::Bloom)->Mapping();
		
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
		CONST_BUFFER(ConstantBufferType::Bloom)->PushData(&mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->bloomParams, sizeof(BloomParams));
		mpShader->Update();
	}

	void Material::PushGraphicDataExceptForShader(int _containerIndex, int _subsetIndex)
	{
		CONST_BUFFER(ConstantBufferType::Material)->PushData(&mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->materialParams, sizeof(MaterialParams));
		CONST_BUFFER(ConstantBufferType::Bloom)->PushData(&mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->bloomParams, sizeof(BloomParams));

		CONST_BUFFER(ConstantBufferType::Material)->Mapping();
		CONST_BUFFER(ConstantBufferType::Bloom)->Mapping();

		for (int i = 0; i < TEXTURE_VALUE_COUNT; ++i)
		{
			if (nullptr == mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->textures[i])
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
					mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->textures[i]->GetSRV().GetAddressOf());

				CONTEXT->GSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->textures[i]->GetSRV().GetAddressOf());

				CONTEXT->CSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->textures[i]->GetSRV().GetAddressOf());

				CONTEXT->VSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->textures[i]->GetSRV().GetAddressOf());

				CONTEXT->DSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->textures[i]->GetSRV().GetAddressOf());

				CONTEXT->HSSetShaderResources(static_cast<int>(RegisterSRV::t0) + i, 1,
					mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->textures[i]->GetSRV().GetAddressOf());
			}

		}
	}


	void Material::PushComputeData()
	{
		CONST_BUFFER(ConstantBufferType::Material)->PushData(&mMaterialContainerVec[0]->materialSubsetVec[0]->materialParams, sizeof(MaterialParams));
		CONST_BUFFER(ConstantBufferType::Bloom)->PushData(&mMaterialContainerVec[0]->materialSubsetVec[0]->bloomParams, sizeof(BloomParams));
		
		CONST_BUFFER(ConstantBufferType::Material)->Mapping();
		CONST_BUFFER(ConstantBufferType::Bloom)->Mapping();
		mpShader->Update();
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

	void Material::PushInputLayout()
	{
		mpShader->PushInputLayout();
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
		mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->materialParams.SetVec4(_index, Vec4(_value.x, _value.y, _value.z, 1.f));
	}

	void Material::SetVec4(int _index, Vec4 _value, int _containerIndex, int _subsetIndex)
	{
		mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->materialParams.SetVec4(_index, _value);
	}

	void Material::SetVec4AllSubset(int _index, Vec4 _value)
	{
		for (int i = 0; i < mMaterialContainerVec.size(); ++i)
		{
			for (int j = 0; j < mMaterialContainerVec[i]->materialSubsetVec.size(); ++j)
			{
				mMaterialContainerVec[i]->materialSubsetVec[j]->materialParams.SetVec4(_index, _value);
			}
		}
	}

	void Material::SetMatrix(int _index, Matrix _value, int _containerIndex, int _subsetIndex)
	{
		mMaterialContainerVec[_containerIndex]->materialSubsetVec[_subsetIndex]->materialParams.SetMatrix(_index, _value);
	}

	shared_ptr<Material> Material::Clone()
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		pMaterial->ClearMaterialContainers();

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

		if (0 == mMaterialContainerVec.size())
		{
			pMaterial->AddMaterialContainer(new MaterialContainer);
			MaterialContainer* pContainer = pMaterial->GetMaterialContainer(0);
			pContainer->AddSubset(new MaterialSubset);
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
	void Material::SaveTexture(FILE* _pFile, shared_ptr<Texture> _pTexture)
	{
		AssertEx(nullptr != _pFile, L"Material::SaveTexture() - 파일 포인터가 nullptr이다");

		wstring name = _pTexture->GetName();
		UINT32 nameCount = static_cast<UINT32>(name.size());
		fwrite(&nameCount, sizeof(UINT32), 1, _pFile);
		fwrite(name.data(), sizeof(wchar_t), name.size(), _pFile);

		wstring path = _pTexture->GetPath();
		UINT32 pathCount = static_cast<UINT32>(path.size());
		fwrite(&pathCount, sizeof(UINT32), 1, _pFile);
		fwrite(path.data(), sizeof(wchar_t), path.size(), _pFile);
	}
}


