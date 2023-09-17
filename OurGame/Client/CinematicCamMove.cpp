#include "pch.h"
#include "CinematicCamMove.h"
#include "Player.h"
#include "SceneManager.h"
#include "Transform.h"

namespace yj
{
	CinematicCamMove::CinematicCamMove()
		:pCamera(nullptr)
	{
	}

	void CinematicCamMove::Initialize()
	{
		GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera()->GetCamera();
	}

	Component* CinematicCamMove::Clone(GameObject* _pGameObject)
	{
		return nullptr;
	}

	void CinematicCamMove::CamEventTrigger(const int _event_num)
	{
		switch (_event_num)
		{
		case 1:
			//PLAYER.ControlAble;
			//플레이어 조작 금지

			isEventOn = true;
			//Vec3
			//break;

		}
	}

	void CinematicCamMove::Update()
	{
		//평소에는 플레이어의 어디 위치에서 따라 오게
		if (!isEventOn)
		{
			GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera()->GetCamera()->GetTransform()->SetPosition(Vec3());
		}

		if (this->GetName() == L"FirstEventCamera")
		{
			
		}

		if (isEventOn)
		{
			if (mPlayedNum == 0)
			{
				return;
			}
			else
			{
				if (mPlayedNum == 1)
				{
					
				}
			}
		}
	}
	void CinematicCamMove::MoveTo(Vec3 _dot_a, Vec3 _dot_b)
	{
		/*Vec3 mDotA = _dot_a;
		Vec3 mDotB = _dot_b;

		Vec3 mDotC = mDotA - mDotB;

		float R = sqrt(pow(mDotC.x,2) + pow(mDotC.y,2));
		Vec3 dir = Vec3(mDotC.x / R, mDotC.y / R, mDotC.z / R);*/

		Vec3 A = _dot_a;
		Vec3 B = _dot_b;
		Vec3 mDir = B - A;
		Vec3 mNomalizedDir;
		mDir.Normalize(mNomalizedDir);
		//Vec3 mLeft = XMVector3Cross(mdir, Vec3::Up);
		//Vec3 mfixedLeft;
		//mLeft.Normalize(mfixedLeft);
		Quaternion mQA = Vec4(_dot_a.x, _dot_a.y, _dot_a.z, 1.0f);
		Quaternion mQB = Vec4(_dot_b.x, _dot_b.y, _dot_b.z, 1.0f);
		
		Quaternion::Slerp(mQA, mQB, 2);
	}	


	void CinematicCamMove::RotateTo()
	{
	}
}