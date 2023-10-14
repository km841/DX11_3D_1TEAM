#pragma once
#include "Monster.h"
#include "TimerObject.h"
class LORD_BOSS_ROLL;
class MonsterSlowObject;
class LORD_BOSS :
    public Monster
{
public:
	LORD_BOSS();
	virtual ~LORD_BOSS();
	LORD_BOSS* Clone()
	{
		LORD_BOSS* pLORD_BOSS = GameObject::Clone<LORD_BOSS>();
		return pLORD_BOSS;
	}

	virtual void SetBehaviorTree();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void OnCollisionEnter(Collider* _pOtherCollider); //다이나믹,스태틱이 충돌 일어났을떄 이함수로
	virtual void OnCollisionStay(Collider* _pOtherCollider);
	virtual void OnCollisionExit(Collider* _pOtherCollider);

	virtual void OnTriggerEnter(Collider* _pOtherCollider); //키네틱이 충돌이일어났을때 이함수로
	virtual void OnTriggerStay(Collider* _pOtherCollider);
	virtual void OnTriggerExit(Collider* _pOtherCollider);

public:
	void SetObject(LORD_BOSS_ROLL* _obj) { pObject = _obj; }

	void CutSceneEnd() { isCutSceneEnd = true; }

private:
	
	void SlowTurnLive();
	void SlowTurn(); // 안씀
	void Follow(); // 안씀 
	void PrevFollowSet();
	void PrevFollowLive();
	void PrevRollLive();
	bool LookRay(); // 안씀

	//레이저 패턴때 쓰는 이동+회전
	void LaserFollow_Turn();
	void LaserPrevFollowSet();
	void LaserPrevFollowLive();
	void CreateCow(Vec3 _pos);

	//공격 콜라이더 오브젝트
	void MonsterAttackCol();
	void MonsterSilent_ClapCol();
	void MonsterBackswingCol();

	//투사체 공격(항아리던지기)
	void CreatePOTProJectTile();
	void CreatePOTProJectTile(int _a);
private:
	Vec3 RotDir;
	Vec3 PosDir;
	Vec3 PrevDir;

	Vec3 PotProjectPos;

	Vec3 LaserPos = Vec3(14.5f, 10.f, -10.f);
	Vec3 LaserRot = Vec3(-90.f, 360.f, 130.f);

	int Health;
	float TurnSpeed;
	float mMagnScale;
	bool isGround = false;
	bool isWall = false;
	bool isCrash = true;
	bool isSilent_Clap = false;
	bool isCutSceneEnd = false;

	MonsterBasicState PrevState;

	LORD_BOSS_ROLL* pObject;
	GameObject* pMonsterAttackCol;
	MonsterSlowObject* pMonsterSilent_ClapCol;
	GameObject* pBackswingCol;

	TimerObject mTimer;
private:
	//사운드 관련 bool
	bool isMelee_Jump01 = true;
	bool isMelee_Jump02 = true;
	bool isMelee_Jump03 = true;
	bool isMelee_Slam01 = true;
	bool isMelee_Slam02 = true;
	bool isMelee_Slam03 = true;

	bool isBackSwing = true;

	bool isLaser = true;

	bool isLandSlam = true;

	bool isBall = true;

	bool isRollWall = true;

};

