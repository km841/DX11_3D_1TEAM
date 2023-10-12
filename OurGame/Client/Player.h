#pragma once
#include "GameObject.h"
#include "HpUi.h"
class SwordScript;
class BowScript;
class ArrowScript;
class SwordScript;
class SwordHeavyEffect;
class State;


#define P_UP PLAYER->GetKeyInfo().eForwardKey
#define P_DOWN PLAYER->GetKeyInfo().eBackwardKey
#define P_LEFT PLAYER->GetKeyInfo().eLeftKey
#define P_RIGHT PLAYER->GetKeyInfo().eRightKey

class Player :
    public GameObject
{
public:
	
    Player();
	virtual ~Player();
	Player* Clone()
	{
		Player* pPlayer = GameObject::Clone<Player>();
		return pPlayer;
	}

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void OnCollisionEnter(Collider* _pOtherCollider);
	virtual void OnCollisionStay(Collider* _pOtherCollider);
	virtual void OnCollisionExit(Collider* _pOtherCollider);

	virtual void OnTriggerEnter(Collider* _pOtherCollider);
	virtual void OnTriggerStay(Collider* _pOtherCollider);
	virtual void OnTriggerExit(Collider* _pOtherCollider);

public:
	void StateChange(PlayerState _eState);

	void SetDirectionChange(DirectionEvasion _eState);
	DirectionEvasion GetDirectioninfo() { return meDirectionEvasion; }

	float GetAttackSpeed() { return mAttack_Speed; }
	void SetAttackSpeed(float _attackspeed) { mAttack_Speed = _attackspeed; }

	float GetMoveSpeed() { return mSpeed; }
	void SetMoveSpeed(float _speed) { mSpeed = _speed; }

	int GetHP() { return mHP; }
	void RecoverHP(){ mHP = 4; } // 피 최대회복
	void DamegeHP()  // 피깍이는거
	{
		if (mHP <= 0)
			return;
		mHP--;
	}

	int GetCost() { return mCost; }
	void SetCost(int  _cost) { mCost = _cost; }
	void DamegeCost() //마나 깎이는거
	{
		if (mCost <= 0)
			return;
		mCost--;
	}
	void RecoverCost() // 마나 회복
	{
		if (mCost >= 5)
			return;
		mCost++;
	}

	float GetAttackDamage() { return mAttackDamage; }
	void SetAttackDamage(float _Damage) { mAttackDamage = _Damage; }

	float GetDashSpeed() { return mDash_Speed; }
	void SetDashSpeed(float _Dash_Speed) { mDash_Speed = _Dash_Speed; }

	bool GetAttackDir() { return mbAttackDir; }
	void SetAttackDir(bool _AttackDir) { mbAttackDir = _AttackDir; }

	bool GetisClimb() { return isClimb; }
	void SetisClimb(bool _isClimb) { isClimb = _isClimb; }

	Vec3 GetToMovePos() { return ToMovePos; }
	void SetToMovePos(Vec3 _Pos) { ToMovePos = _Pos; }

	Vec3 GetToDownPos() { return ToDownPos; }
	void SetToDownPos(Vec3 _Pos) { ToDownPos = _Pos; }

	DirectionEvasion GetToRotPos() { return ToRotPos; }
	void SetToRotPos(DirectionEvasion _dir) { ToRotPos = _dir; }

	wstring GetLadderName() { return lastLadderName; }

	GameObject* GetGreatSword() { return pGreatSword; }
	GameObject* GetAttackCol() { return pAttackCol; }
	GameObject* GetBow() { return pBow; }
	GameObject* GetArrow() { return pArrow; }
	
	const PlayerKeyInfo& GetKeyInfo() { return mKeyInfo; }

	SwordHeavyEffect* GetSwordEffect() { return mpSlashEffect; }

public:
	
	static Player* spPlayer;
	static Player* GetPlayer();

	State* mState[PLAYER_STATE_COUNT]; //조건 확인용
    State* mActiveState; //현재 상태 확인

	PlayerKeyInfo mKeyInfo;
	

	
private:


	
private:
	int mHP;
	int mCost;
	float mSpeed;
	float mDash_Speed;
	float mAttackDamage;
	float mAttack_Speed;
	bool mbAttackDir;


	int mGroundCount;

	bool isClimb=false;
	wstring lastLadderName;
	Vec3 ToMovePos;
	Vec3 ToDownPos;
	DirectionEvasion ToRotPos;



	SwordHeavyEffect* mpSlashEffect;
	DirectionEvasion meDirectionEvasion; // 이동 상태 FSM

	GameObject* pGreatSword;
	SwordScript* pSwordSc;
	GameObject* pAttackCol;

	GameObject* pBow;
	BowScript* pBowSc;
	GameObject* pArrow;
	ArrowScript* pArrowSc;
};

