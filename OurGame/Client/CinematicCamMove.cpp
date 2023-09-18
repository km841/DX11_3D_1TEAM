#include "pch.h"
#include "CinematicCamMove.h"
#include "Player.h"
#include "SceneManager.h"
#include "Transform.h"

namespace yj
{
	CinematicCamMove::CinematicCamMove()
		:pCamera(nullptr),
		isEventOn(false),
		GameObject(LayerType::Ground)
	{
	}

	void CinematicCamMove::Initialize()
	{
		GameObject::Initialize();
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
		GameObject::Update();
		if (GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera()->GetCamera() == nullptr)
		{
			return;
		}
		this->GetTransform()->SetPosition(GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera()->GetCamera()->GetTransform()->GetPosition());
		//평소에는 플레이어의 어디 위치에서 따라 오게
		if (!isEventOn)
		{
			Vec3 mPlayerPos = PLAYER->GetTransform()->GetPosition();
			Transform* mCamTr = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera()->GetCamera()->GetTransform();
			Vec3 mFiexedPos = Vec3(mPlayerPos.x - 20, mPlayerPos.y + 20, mPlayerPos.z + 20 );
			mCamTr->SetPosition(mFiexedPos);
			Vec3 mCamPos = mCamTr->GetPosition();

			 Quaternion mCamQuater =  mCamTr->EulerToQuaternion(mCamTr->GetRotation());
			 Quaternion mPlayerQuater = PLAYER->GetTransform()->EulerToQuaternion(PLAYER->GetTransform()->GetRotation());
			 Quaternion mResult = mCamQuater.LookRotation(mPlayerPos - mCamPos,mCamPos.Up); 
			/* Vec3 mResultVec3 = mResult.ToEuler();
			 mCamTr->SetRotation(mResultVec3 * 100);*/
			int c = 0;
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


	float CinematicCamMove::Dot(Vec3 a, Vec3 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	float CinematicCamMove::Mag(Vec3 a)
	{
		return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	}

}