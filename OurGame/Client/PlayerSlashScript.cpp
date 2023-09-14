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
	if (IS_DOWN(KeyType::LBUTTON))
	{
		mbReverse = !mbReverse;
		Attack();
	}

	mElapsedTime += DELTA_TIME;
	GetMeshRenderer()->GetMaterial()->SetFloat(0, mElapsedTime);
	GetMeshRenderer()->GetMaterial()->SetFloat(1, mEndTime);
	GetMeshRenderer()->GetMaterial()->SetFloat(2, mAttackSpeed);
	GetMeshRenderer()->GetMaterial()->SetInt(1, static_cast<int>(mbReverse));
}

Component* PlayerSlashScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new PlayerSlashScript);
}
