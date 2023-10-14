#include "pch.h"
#include "KeyDoor.h"

namespace yj
{
	KeyDoor::KeyDoor()
		:GameObject(LayerType::DecoObject)
	{
		mName = L"KeyDoor";
	}
	
	KeyDoor::~KeyDoor()
	{
	}
	void KeyDoor::Initialize()
	{
		GameObject::Initialize();
	}
	void KeyDoor::Update()
	{
		GameObject::Update();
	}
}