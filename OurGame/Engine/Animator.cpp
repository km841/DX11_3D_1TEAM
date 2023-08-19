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
	{
		mpComputeMaterial = GET_SINGLE(Resources)->Get<Material>(L"ComputeAnimation");
	}
	Animator::~Animator()
	{
		for (int i = 0; i < mFrameContainer.size(); ++i)
		{
			SAFE_DELETE(mFrameContainer[i]);
		}
		mFrameContainer.clear();
	}
	// 이후에 작업 예정
	Component* Animator::Clone(GameObject* _pGameObject)
	{
		Animator* pAnimator = new Animator;
		return pAnimator;
	}
	void Animator::FinalUpdate()
	{
		int count = static_cast<int>(mAnimContainer.size());

		for (int i = 0; i < count; ++i)
		{
			FrameInfo& fi = mFrameContainer[i]->frameInfo;
			fi.updateTime += DELTA_TIME;

			const AnimClipInfo& animClip = mAnimContainer[i]->animClips.at(fi.clipIndex);
			if (fi.updateTime >= animClip.duration)
				fi.updateTime = 0.f;

			const int ratio = static_cast<int>(animClip.frameCount / animClip.duration);
			fi.frame = static_cast<int>(fi.updateTime * ratio);
			fi.frame = min(fi.frame, animClip.frameCount - 1);
			fi.nextFrame = min(fi.frame + 1, animClip.frameCount - 1);
			fi.frameRatio = static_cast<float>(fi.frame - fi.frame);
		}
	}
	void Animator::Play(int _idx, int _containerIndex)
	{
		AssertEx(_idx < mAnimContainer[_containerIndex]->animClips.size(), L"Animator::Play() - 해당 인덱스에 해당하는 애니메이션 클립 없음");
		mFrameContainer[_containerIndex]->frameInfo.clipIndex = _idx;
		mFrameContainer[_containerIndex]->frameInfo.updateTime = 0.f;
	}
	void Animator::SetBones(const std::vector<BoneInfo>& _bones, int _containerIndex)
	{
		mAnimContainer[_containerIndex]->bones = _bones;
	}
	void Animator::SetAnimClip(const std::vector<AnimClipInfo>& _animClips, int _containerIndex)
	{
		mAnimContainer[_containerIndex]->animClips = _animClips;
	}
	void Animator::PushData(int _containerIndex)
	{
		AssertEx(false == mAnimContainer.empty(), L"Animator::PushData() - 애니메이션 컨테이너가 비어 있음, 애니메이션이 제대로 로드되지 않음");
		AssertEx(false == mFrameContainer.empty(), L"Animator::PushData() - 프레임 컨테이너가 비어 있음. SetAnimContainer() 먼저 호출해야 함.");

		AnimationContainer* pAc = mAnimContainer[_containerIndex];
		FrameContainer* pFc = mFrameContainer[_containerIndex];

		UINT32 boneCount = static_cast<UINT32>(pAc->bones.size());
		if (pFc->pBoneFinalMatrix->GetElementCount() < static_cast<int>(boneCount))
			pFc->pBoneFinalMatrix->Create(sizeof(Matrix), boneCount);

		// Compute Shader
		shared_ptr<Mesh> pMesh = GetMeshRenderer()->GetMesh();
		pMesh->GetBoneFrameDataBuffer(pFc->frameInfo.clipIndex, _containerIndex)->PushGraphicsData(RegisterSRV::t8);
		pMesh->GetBoneOffsetBuffer(_containerIndex)->PushGraphicsData(RegisterSRV::t9);

		pFc->pBoneFinalMatrix->PushComputeUAVData(RegisterUAV::u0);

		mpComputeMaterial->SetInt(0, boneCount);
		mpComputeMaterial->SetInt(1, pFc->frameInfo.frame);
		mpComputeMaterial->SetInt(2, pFc->frameInfo.nextFrame);
		mpComputeMaterial->SetFloat(0, pFc->frameInfo.frameRatio);

		UINT32 groupCount = (boneCount / 256) + 1;
		mpComputeMaterial->Dispatch(groupCount, 1, 1);

		// Graphics Shader
		pFc->pBoneFinalMatrix->PushGraphicsData(static_cast<RegisterSRV>(16));
	}
	void Animator::SetAnimContainer(const std::vector<AnimationContainer*>& _animContainer)
	{
		mAnimContainer = _animContainer;
		int containerSize = static_cast<int>(_animContainer.size());

		for (int i = 0; i < containerSize; ++i)
		{
			FrameContainer* pFrameContainer = new FrameContainer;
			pFrameContainer->pBoneFinalMatrix = make_shared<StructuredBuffer>();

			mFrameContainer.push_back(pFrameContainer);
		}
	}
}