#include "pch.h"
#include "ExplosionScript.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Timer.h"
#include "RigidBody.h"
#include "Transform.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "RenderManager.h"
namespace hm
{
	ExplosionScript::ExplosionScript(GameObject* _pBoss)
		: mpBoss(_pBoss)
		, mAccTime(0.f)
	{
		mBigTimer.SetEndTime(2.2f);
		mBigTimer.Start();

		mDeathTimer.SetEndTime(3.f);
		mDeathTimer.Start();
	}
	void ExplosionScript::Initialize()
	{
	}
	void ExplosionScript::FixedUpdate()
	{
		mAccTime += DELTA_TIME;
		GetMeshRenderer()->GetMaterial()->SetFloat(0, mAccTime);

		Transform* pTr = GetTransform();
		RigidBody* pRb = GetRigidBody();
		/*Vec3 TextureSize = pTr->GetScale();
		Vec3 ColSize = pRb->GetGeometrySize();*/


		mBigTimer.Update();
		
		if (mBigTimer.IsFinished())
		{
			mBigTimer.Stop();
			pRb->SetGeometrySize(Vec3(18.f,17.f,18.f));
			pTr->SetScale(Vec3(18.f, 17.f, 18.f));

			GET_SINGLE(RenderManager)->AddCameraShakeEffect(0.3f, 0.4f, 0);
			GET_SINGLE(RenderManager)->AddChromaticEffect(0.3f, nullptr, nullptr, 1);
			GET_SINGLE(RenderManager)->SetBloomScale(5.0f);
		}

		mDeathTimer.Update();
		if(mDeathTimer.IsFinished()) //삭제되는 부분
		{
			mDeathTimer.Stop();
			GET_SINGLE(RenderManager)->SetBloomScale(1.0f);
			MapType type = GET_SINGLE(SceneManager)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(type, static_cast<GameObject*>(GetGameObject()));

		}
	}
	Component* ExplosionScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new ExplosionScript(mpBoss));
	}
}