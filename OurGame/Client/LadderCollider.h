#pragma once
#include "GameObject.h"
class LadderCollider :
    public GameObject
{
public:
	LadderCollider();
	virtual ~LadderCollider();
	LadderCollider* Clone()
	{
		LadderCollider* pLadderColObj = GameObject::Clone<LadderCollider>();
		return pLadderColObj;
	}

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy();

	Vec3 GetPlayerToMovePos() { return mPlayerToMovePos; }
	void SetPlayerToMovePos(Vec3 _Pos) { mPlayerToMovePos = _Pos; }

	Vec3 GetPlayerToDownPos() { return mPlayerToDownPos; }
	void SetPlayerToDownPos(Vec3 _Pos) { mPlayerToDownPos = _Pos; }

	DirectionEvasion GetDir() { return mDir; }
	void SetDir(DirectionEvasion _dir) { mDir = _dir; }

private:
	Vec3 mPlayerToMovePos = Vec3::Zero;
	Vec3 mPlayerToDownPos = Vec3::Zero;

	Vec3 Rot = Vec3::Zero;

	DirectionEvasion mDir = DirectionEvasion::NONE;
};

