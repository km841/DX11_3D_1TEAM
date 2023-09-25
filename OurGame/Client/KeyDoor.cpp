#include "pch.h"
#include "KeyDoor.h"

namespace yj
{
	KeyDoor::KeyDoor()
		:GameObject(LayerType::DecoObject)
	{
		
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