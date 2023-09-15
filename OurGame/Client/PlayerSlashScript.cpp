#include "pch.h"
#include "PlayerSlashScript.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Timer.h"
#include "Input.h"

PlayerSlashScript::PlayerSlashScript()
	: mElapsedTime(0.f)
	, mbEnable(false)
	, mEndTime(0.4f)
	, mAttackSpeed(5.f)
	, mbReverse(true)
{
}

void PlayerSlashScript::FixedUpdate()
{
	/*if (IS_DOWN(KeyType::LBUTTON))
	{
		Attack();
	}*/

	mElapsedTime += DELTA_TIME;
	GetMeshRenderer()->GetMaterial()->SetFloat(0, mElapsedTime);
	GetMeshRenderer()->GetMaterial()->SetFloat(1, mEndTime);
	GetMeshRenderer()->GetMaterial()->SetFloat(2, mAttackSpeed);
	GetMeshRenderer()->GetMaterial()->SetInt(1, static_cast<int>(mbReverse));

	GetMeshRenderer()->GetMaterial()->SetBloom(true);
	GetMeshRenderer()->GetMaterial()->SetBloomPower(2.0f);
	GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 0.f, 0.f, 1.f));
}

Component* PlayerSlashScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new PlayerSlashScript);
}

void PlayerSlashScript::ChangeReverse()
{
	if (mbReverse == true)
		mbReverse = false;
	else
		mbReverse = true;
}
