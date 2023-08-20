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
		pBoneFinalMatrix = make_shared<StructuredBuffer>();

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
		updateTime += DELTA_TIME;

		const AnimClipInfo& animClip = animClips->at(clipIndex);
		if (updateTime >= animClip.duration)
			updateTime = 0.f;

		const int ratio = static_cast<int>(animClip.frameCount / animClip.duration);
		frame = static_cast<int>(updateTime * ratio);
		frame = min(frame, animClip.frameCount - 1);
		nextFrame = min(frame + 1, animClip.frameCount - 1);
		frameRatio = static_cast<float>(frame - frame);
	}
	void Animator::Play(int _idx)
	{
		AssertEx(_idx < animClips->size(), L"Animator::Play() - 해당 인덱스에 해당하는 애니메이션 클립 없음");
		clipIndex = _idx;
		updateTime = 0.f;
	}
	void Animator::SetBones(const std::vector<BoneInfo>* _bones)
	{
		bones = _bones;
	}
	void Animator::SetAnimClip(const std::vector<AnimClipInfo>* _animClips)
	{
		animClips = _animClips;
	}
	void Animator::PushData()
	{
		int boneCount = static_cast<int>(bones->size());
		if (pBoneFinalMatrix->GetElementCount() < boneCount)
			pBoneFinalMatrix->Create(sizeof(Matrix), boneCount);

		// Compute Shader
		shared_ptr<Mesh> mesh = GetGameObject()->GetMeshRenderer()->GetMesh();
		mesh->GetBoneFrameDataBuffer(clipIndex)->PushGraphicsData(RegisterSRV::t8);
		mesh->GetBoneOffsetBuffer()->PushGraphicsData(RegisterSRV::t9);

		pBoneFinalMatrix->PushComputeUAVData(RegisterUAV::u0);

		mpComputeMaterial->SetInt(0, boneCount);
		mpComputeMaterial->SetInt(1, frame);
		mpComputeMaterial->SetInt(2, nextFrame);
		mpComputeMaterial->SetFloat(0, frameRatio);

		UINT32 groupCount = (boneCount / 256) + 1;
		mpComputeMaterial->Dispatch(groupCount, 1, 1);

		// Graphics Shader
		pBoneFinalMatrix->PushGraphicsData(static_cast<RegisterSRV>(16));
	}
}