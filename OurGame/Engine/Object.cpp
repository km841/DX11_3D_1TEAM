#include "pch.h"
#include "Object.h"

namespace hm
{
	Object::Object(ObjectType _eObjectType)
		: meObjectType(_eObjectType)
	{
		static UINT32 sGenID = 1;
		mID = sGenID++;
	}

	Object::~Object()
	{
	}
}
