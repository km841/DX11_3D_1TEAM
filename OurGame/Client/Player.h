#pragma once
#include "GameObject.h"
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

public:
	static Player* spPlayer;
	static Player* GetPlayer();

	State* mState[PLAYER_STATE_COUNT]; //조건 확인용
    State* mActiveState; //현재 상태 확인

};

