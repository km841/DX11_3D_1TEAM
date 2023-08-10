#pragma once
#include "GameObject.h"
class Player :
    public GameObject
{
public:
    Player();
	virtual ~Player();
	Player* Clone()
	{
		Player* pPlayer = GameObject::Clone<Player>();
		pPlayer->mState = mState;
		pPlayer->mpItem = mpItem->Clone<GameObject>(LayerType::Unknown);
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
	void SetItem(GameObject* _pItem) { mpItem = _pItem; }
	void SetState(int _state) { mState = _state; }

private:
	int mState;
	GameObject* mpItem;

	
};

