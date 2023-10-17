#include "pch.h"
#include "EndingLogoScript.h"
#include "Transform.h"
#include "AudioSound.h"
#include "SceneManager.h"

hm::EndingLogoScript::EndingLogoScript()
    : mbIsSoundBegin(false)
{
    mWaitTimer.SetEndTime(1.f);
    mTimer.SetEndTime(0.3f);
    mTopMovingTimer.SetEndTime(1.f);
    mTopMovingBeginTimer.SetEndTime(1.f);

    mWaitTimer.Start();

}

void hm::EndingLogoScript::FixedUpdate()
{
    mWaitTimer.Update();
    if (true == mWaitTimer.IsFinished())
    {
        mTimer.Start();
    }
    
    mTimer.Update();
    if (mTimer.GetIsRun())
    {
        float endWidth = 400.f;
        float endHeight = 230.f;
        GetTransform()->SetScale(Lerp(Vec3(endWidth * 2.f, endHeight * 2.f, 1.f), Vec3(endWidth, endHeight, 1.f), mTimer.GetProgress()));
    }
    else
    {
        GetTransform()->SetScale(Vec3::Zero);
    }

    if (mTimer.IsFinished())
    {
        GetTransform()->SetScale(Vec3(400.f, 230.f, 1.f));

        if (false == mbIsSoundBegin)
        {
            mbIsSoundBegin = true;
            GetAudioSound()->SetSound(L"LogoBegin", ACTIVE_SCENE, false, "..\\Resources\\Sound\\LogoBeginSound.wav");
            GetAudioSound()->Play(20);
        }
    }
}

Component* hm::EndingLogoScript::Clone(GameObject* _pGameObject)
{
    return nullptr;
}
