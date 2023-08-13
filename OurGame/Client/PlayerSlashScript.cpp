#include "pch.h"
#include "PlayerSlashScript.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Timer.h"

PlayerSlashScript::PlayerSlashScript()
	: mElapsedTime(0.f)
{
}

void PlayerSlashScript::FixedUpdate()
{
	mElapsedTime += DELTA_TIME;
	GetMeshRenderer()->GetMaterial()->SetFloat(0, mElapsedTime);
}

Component* PlayerSlashScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new PlayerSlashScript);
}
