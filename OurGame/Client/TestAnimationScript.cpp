#include "pch.h"
#include "TestAnimationScript.h"
#include "GameObject.h"
#include "Input.h"
#include "Animator.h"

namespace hm
{
	TestAnimationScript::TestAnimationScript()
	{
	}
	Component* TestAnimationScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new TestAnimationScript);
	}
	void TestAnimationScript::FixedUpdate()
	{
		if (IS_DOWN(KeyType::N_1))
		{
			int count = GetAnimator()->GetAnimCount();
			int currentIndex = GetAnimator()->GetCurrentClipIndex();

			int index = (currentIndex + 1) % count;
			GetAnimator()->Play(index);
		}

		if (IS_DOWN(KeyType::N_2))
		{
			int count = GetAnimator()->GetAnimCount();
			int currentIndex = GetAnimator()->GetCurrentClipIndex();

			int index = (currentIndex - 1 + count) % count;
			GetAnimator()->Play(index);
		}

		if (IS_DOWN(KeyType::N_3))
		{
			bool bFinFlag = GetAnimator()->IsFinished();

			GetAnimator()->Play(L"PotHead_Idle");
			GetAnimator()->SetHasExitFlag(false);

		}
	}
}