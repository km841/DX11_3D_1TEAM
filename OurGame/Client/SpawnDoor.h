#pragma once
#include "GameObject.h"
#include "Input.h"
#include "PaperBurnScript.h"
#include "TimerObject.h"
#include "Grimace.h"
#include "Bat.h"
#include "HeadRoller.h"
#include "Mage.h"
#include "Lurker.h"
#include "SceneManager.h"

namespace hm
{
	template<typename T>
	class SpawnDoor :
		public GameObject
	{
	public:
		SpawnDoor();
		virtual ~SpawnDoor();
		SpawnDoor* Clone()
		{
			SpawnDoor* pDoor = GameObject::Clone<SpawnDoor>();
			return pDoor;
		}
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

	public:
		void SetPaperBurn();
		static MonsterType GetMonsterType();

	public:
		void SetSpawnFunction(std::function<Monster* ()> _spawnFunc) { mSpawnFunction = _spawnFunc; }
		T* Spawn();

	private:
		std::function<Monster* ()> mSpawnFunction;
		TimerObject mTimer;
		bool mbIsFinished;
		bool mbIsSpawned;
	};


	template<typename T>
	inline SpawnDoor<T>::SpawnDoor()
		: GameObject(LayerType::Effect)
		, mbIsFinished(false)
		, mbIsSpawned(false)
	{
		mTimer.SetEndTime(2.f);
	}
	template<typename T>
	inline SpawnDoor<T>::~SpawnDoor()
	{
	}
	template<typename T>
	inline void SpawnDoor<T>::Initialize()
	{
		GameObject::Initialize();
	}
	template<typename T>
	inline void SpawnDoor<T>::Update()
	{
		if (false == mbIsSpawned && 0.5f < mTimer.GetProgress())
		{
			mbIsSpawned = true;
			T* pMonster = Spawn();
			pMonster->Initialize();
			GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pMonster);
		}

		GameObject::Update();
		mTimer.Update();

		if (mTimer.IsFinished() && false == mbIsFinished)
		{
			mbIsFinished = true;
			GetScript<PaperBurnScript>()->Reset();
			GetScript<PaperBurnScript>()->SetReverse(false);
			GetScript<PaperBurnScript>()->SetSpawnPaperBurn();
			mTimer.Stop();
		}

	}
	template<typename T>
	inline void SpawnDoor<T>::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	template<typename T>
	inline void SpawnDoor<T>::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}
	template<typename T>
	inline void SpawnDoor<T>::Render()
	{
		GameObject::Render();
	}
	template<typename T>
	inline void SpawnDoor<T>::Destroy()
	{
		GameObject::Destroy();
	}
	template<typename T>
	inline void SpawnDoor<T>::SetPaperBurn()
	{
		GetScript<PaperBurnScript>()->SetSpawnPaperBurn();
		GetScript<PaperBurnScript>()->SetReverse(true);
		GetScript<PaperBurnScript>()->SetSpeed(2.f);
		mTimer.Start();
	}
	template<typename T>
	inline T* SpawnDoor<T>::Spawn()
	{
		AssertEx(nullptr != mSpawnFunction, L"SpawnDoor<T>::Spawn() - SpawnFunction이 지정되지 않음");
		return static_cast<T*>(mSpawnFunction());
	}
	template<typename T>
	inline MonsterType SpawnDoor<T>::GetMonsterType()
	{
		if (std::is_same_v<T, Grimace>)
			return MonsterType::Grimace;
		else if (std::is_same_v<T, Bat>)
			return MonsterType::Bat;
		else if (std::is_same_v<T, HeadRoller>)
			return MonsterType::HeadRoller;
		else if (std::is_same_v<T, Mage>)
			return MonsterType::Mage;
		else if (std::is_same_v<T, Lurker>)
			return MonsterType::Lurker;

		else
		{
			AssertEx(false, L"잘못된 타입 전달");
			return MonsterType::End;
		}
	}
}


