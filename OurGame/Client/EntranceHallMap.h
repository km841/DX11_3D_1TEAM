#pragma once
#include "Map.h"

#include "DecoObject.h"
#include "KeyPot.h"


class EntranceHallMap :
    public Map
{
public:
	EntranceHallMap();
	virtual ~EntranceHallMap();

public:
	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();

	virtual void Enter();
	virtual void Exit();

public:

		void InitObjectAdd();
		void InitColliderAdd();

private:
	DecoObject* pJarLDoor;
	DecoObject* pJarRDoor;
	yj::KeyPot* pPot1;
	yj::KeyPot* pPot2;
	int mSpawnPoint = -1;
};

