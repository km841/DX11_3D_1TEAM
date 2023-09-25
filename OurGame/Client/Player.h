#pragma once
#include "GameObject.h"
class SwordScript;
class BowScript;
class ArrowScript;
class SwordScript;
class SwordHeavyEffect;
class State;
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

	float GetAttackDamage() { return mAttackDamage; }
	void SetAttackDamage(float _Damage) { mAttackDamage = _Damage; }

	float GetDashSpeed() { return mDash_Speed; }
	void SetDashSpeed(float _Dash_Speed) { mDash_Speed = _Dash_Speed; }

	bool GetAttackDir() { return mbAttackDir; }
	void SetAttackDir(bool _AttackDir) { mbAttackDir = _AttackDir; }

	bool GetisClimb() { return isClimb; }
	void SetisClimb(bool _isClimb) { isClimb = _isClimb; }

	wstring GetLadderName() { return lastLadderName; }

	GameObject* GetGreatSword() { return pGreatSword; }
	GameObject* GetAttackCol() { return pAttackCol; }
	GameObject* GetBow() { return pBow; }
	GameObject* GetArrow() { return pArrow; }
	
	GameObject* GetLadderEnter() { return pLadderEnter; }
	GameObject* GetLadderExit() { return pLadderExit; }

	SwordHeavyEffect* GetSwordEffect() { return mpSlashEffect; }
public:
	static Player* spPlayer;
	static Player* GetPlayer();

	State* mState[PLAYER_STATE_COUNT]; //조건 확인용
    State* mActiveState; //현재 상태 확인

	
	

	
private:
	int GetHp() { return mHP; }


	
private:
	int mHP;
	int mCost;
	float mSpeed;
	float mDash_Speed;
	float mAttackDamage;
	float mAttack_Speed;
	bool mbAttackDir;

	bool isClimb=false;
	wstring lastLadderName;

	GameObject* pLadderEnter;
	GameObject* pLadderExit;

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

