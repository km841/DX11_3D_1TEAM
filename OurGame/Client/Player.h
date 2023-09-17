#pragma once
#include "GameObject.h"


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
	virtual void OnTriggerEnter(Collider* pOtherCollider);
	virtual void OnTriggerStay(Collider* pOtherCollider);
	virtual void OnTriggerExit(Collider* pOtherCollider);

public:
	void StateChange(PlayerState _eState);

	void SetDirectionChange(DirectionEvasion _eState);
	DirectionEvasion GetDirectioninfo() { return meDirectionEvasion; }

	float GetAttackSpeed() { return mAttack_Speed; }
	void SetAttackSpeed(float _attackspeed) { mAttack_Speed = _attackspeed; }

	float GetMoveSpeed() { return mSpeed; }
	void SetMoveSpeed(float _speed) { mSpeed = _speed; }

	float GetDashSpeed() { return mDash_Speed; }
	void SetDashSpeed(float _Dash_Speed) { mDash_Speed = _Dash_Speed; }

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
	float mAttack;
	float mAttack_Speed;

	GameObject* pGreatSword;
	SwordHeavyEffect* mpSlashEffect;
	DirectionEvasion meDirectionEvasion; // 이동 상태 FSM
};

