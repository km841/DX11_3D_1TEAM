#include "pch.h"
#include "SwordHeavyEffect.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Engine.h"
#include "PlayerSlashScript.h"

SwordHeavyEffect::SwordHeavyEffect()
{
}

SwordHeavyEffect::~SwordHeavyEffect()
{
}

void SwordHeavyEffect::Initialize()
{
	Effect::Initialize();
}

void SwordHeavyEffect::Update()
{
	Effect::Update();
}

void SwordHeavyEffect::FixedUpdate()
{
	Effect::FixedUpdate();
}

void SwordHeavyEffect::FinalUpdate()
{
	Effect::FinalUpdate();
}

void SwordHeavyEffect::Render()
{
	Effect::Render();
}

void SwordHeavyEffect::Destroy()
{
	Effect::Destroy();
}

void SwordHeavyEffect::PushBloomData()
{
	PlayerSlashScript* pScript = GetScript<PlayerSlashScript>();
	GetMeshRenderer()->GetMaterial()->GetTexture(0)->PushSRV(RegisterSRV::t0);
	GetMeshRenderer()->GetMaterial()->GetShader()->Update();
	GetMeshRenderer()->GetMaterial()->SetFloat(0, pScript->mElapsedTime);
	GetMeshRenderer()->GetMaterial()->SetFloat(1, pScript->mEndTime);
	GetMeshRenderer()->GetMaterial()->SetFloat(2, pScript->mAttackSpeed);
	GetMeshRenderer()->GetMaterial()->SetInt(1, static_cast<int>(pScript->mbReverse));
	CONST_BUFFER(ConstantBufferType::Material)->PushData(&GetMeshRenderer()->GetMaterial()->GetMaterialSubset(0, 0)->materialParams, sizeof(MaterialParams));
	CONST_BUFFER(ConstantBufferType::Material)->Mapping();

	GetMeshRenderer()->GetMaterial()->SetBloom(true);
	GetMeshRenderer()->GetMaterial()->SetBloomPower(2.0f);
	GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(0.5f, 0.f, 0.f, 1.f));
	CONST_BUFFER(ConstantBufferType::Bloom)->PushData(&GetMeshRenderer()->GetMaterial()->GetMaterialSubset(0, 0)->bloomParams, sizeof(BloomParams));
	CONST_BUFFER(ConstantBufferType::Bloom)->Mapping();
}
