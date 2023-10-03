#include "pch.h"
#include "Animator.h"
#include "Resources.h"
#include "Timer.h"
#include "StructuredBuffer.h"
#include "MeshRenderer.h"

namespace hm
{
	Animator::Animator()
		: Component(ComponentType::Animator)
		, mAfterFrame(-1)
		, mAfterLoop(false)
	{
		mpComputeMaterial = GET_SINGLE(Resources)->Get<Material>(L"ComputeAnimation");
		mpBoneFinalMatrix = make_shared<StructuredBuffer>();
	}
	Animator::~Animator()
	{
	}
	// 이후에 작업 예정
	Component* Animator::Clone(GameObject* _pGameObject)
	{
		Animator* pAnimator = new Animator;
		return pAnimator;
	}
	void Animator::FinalUpdate()
	{
		mUpdateTime += DELTA_TIME;

		const AnimClipInfo& animClip = mAnimClips->at(mClipIndex);
		
		if (mUpdateTime >= animClip.duration)
		{
			if (-1 != mAfterFrame)
			{
				mClipIndex = mAfterFrame;
				(*mAnimClips)[mClipIndex].bLoop = mAfterLoop;
				mAfterFrame = -1;
				mUpdateTime = 0.f;
				return;
			}

			if (true == animClip.bLoop)
				mUpdateTime = 0.f;
			else
				mbIsFinished = true;
		}

		const int ratio = static_cast<int>(animClip.frameCount / animClip.duration);
		mFrame = static_cast<int>(mUpdateTime * ratio);
		mFrame = min(mFrame, animClip.frameCount - 1);
		mNextFrame = min(mFrame + 1, animClip.frameCount - 1);
		mFrameRatio = static_cast<float>(mFrame - mFrame);
	}
	void Animator::Play(int _idx, bool _bLoop)
	{
		AssertEx(_idx < mAnimClips->size(), L"Animator::Play() - 해당 인덱스에 해당하는 애니메이션 클립 없음");
		
		if ((false == mAnimClips->at(mClipIndex).bHasExit) && (mUpdateTime < mAnimClips->at(mClipIndex).duration))
		{
			mAfterFrame = _idx;
			return;
		}

		mClipIndex = _idx;
		(*mAnimClips)[mClipIndex].bLoop = _bLoop;
		mUpdateTime = 0.f;
		mbIsFinished = false;
	}
	void Animator::Play(const wstring& _animName, bool _bLoop)
	{
		mClipIndex = FindAnimationIndex(_animName);
		AssertEx(mClipIndex != -1, L"Animator::Play() - 해당 인덱스에 해당하는 애니메이션 클립 없음");
		Play(mClipIndex, _bLoop);
	}
	int Animator::FindAnimationIndex(const wstring& _animName)
	{
		for (int i = 0; i < mAnimClips->size(); ++i)
		{
			if ((*mAnimClips)[i].animName == _animName)
				return i;
		}

		return -1;
	}
	void Animator::SetBones(std::vector<BoneInfo>* _bones)
	{
		mBones = _bones;
	}
	void Animator::SetAnimClip(std::vector<AnimClipInfo>* _animClips)
	{
		mAnimClips = _animClips;
	}
	void Animator::PushData()
	{
		int boneCount = static_cast<int>(mBones->size());
		if (mpBoneFinalMatrix->GetElementCount() < boneCount)
			mpBoneFinalMatrix->Create(sizeof(Matrix), boneCount);

		// Compute Shader
		shared_ptr<Mesh> pMesh = GetGameObject()->GetMeshRenderer()->GetMesh();
		pMesh->GetBoneFrameDataBuffer(mClipIndex)->PushGraphicsData(RegisterSRV::t8);
		pMesh->GetBoneOffsetBuffer()->PushGraphicsData(RegisterSRV::t9);

		mpBoneFinalMatrix->PushComputeUAVData(RegisterUAV::u0);

		mpComputeMaterial->SetInt(0, boneCount);
		mpComputeMaterial->SetInt(1, mFrame);
		mpComputeMaterial->SetInt(2, mNextFrame);
		mpComputeMaterial->SetFloat(0, mFrameRatio);

		UINT32 groupCount = (boneCount / 256) + 1;
		mpComputeMaterial->Dispatch(groupCount, 1, 1);

		// Graphics Shader
		mpBoneFinalMatrix->PushGraphicsData(static_cast<RegisterSRV>(16));
	}
	void Animator::RenameAnimation(const wstring& _orgName, const wstring& _newName)
	{
		int idx = FindAnimationIndex(_orgName);
		RenameAnimation(idx, _newName);
	}
	void Animator::RenameAnimation(int _index, const wstring& _newName)
	{
		AssertEx(-1 != _index, L"Animator::RenameAnimation() - 해당 이름을 가진 애니메이션을 찾을 수 없음");
		(*mAnimClips)[_index].animName = _newName;
	}
	void Animator::SetLoop(const wstring& _animName, bool _bFlag)
	{
		int idx = FindAnimationIndex(_animName);
		SetLoop(idx, _bFlag);
	}
	void Animator::SetLoop(int _index, bool _bFlag)
	{
		AssertEx(-1 != _index, L"Animator::SetLoop() - 해당 이름을 가진 애니메이션을 찾을 수 없음");
		(*mAnimClips)[_index].bLoop = _bFlag;
	}

	void Animator::SetHasExitFlag(const wstring& _animName, bool _bFlag)
	{
		int idx = FindAnimationIndex(_animName);
		SetHasExitFlag(idx, _bFlag);
	}
	void Animator::SetHasExitFlag(int _index, bool _bFlag)
	{
		AssertEx(-1 != _index, L"Animator::SetLoop() - 해당 이름을 가진 애니메이션을 찾을 수 없음");
		(*mAnimClips)[_index].bHasExit = _bFlag;
	}
	void Animator::SetPlaySpeed(const wstring& _animName, float _playSpeed)
	{
		int idx = FindAnimationIndex(_animName);
		SetPlaySpeed(idx, _playSpeed);
	}
	void Animator::SetPlaySpeed(int _index, float _playSpeed)
	{
		AssertEx(-1 != _index, L"Animator::SetPlaySpeed() - 해당 이름을 가진 애니메이션을 찾을 수 없음");
		(*mAnimClips)[_index].playSpeed = _playSpeed;
	}
}