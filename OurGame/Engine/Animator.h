#pragma once
#include "Component.h"
#include "Mesh.h"
namespace hm
{
	class Material;
	class StructuredBuffer;

	class Animator :
		public Component
	{
	public:
		Animator();
		virtual ~Animator();
		virtual Component* Clone(GameObject* _pGameObject) override;

	public:
		virtual void FinalUpdate() override;

	public:
		void Play(int _idx, int _containerIndex = 0);

		void SetBones(const std::vector<BoneInfo>& _bones, int _containerIndex = 0);
		void SetAnimClip(const std::vector<AnimClipInfo>& _animClips, int _containerIndex = 0);
		void PushData(int _containerIndex = 0);

		int GetAnimCount(int _containerIndex = 0) { return static_cast<UINT32>(mAnimContainer[_containerIndex]->animClips.size()); }
		void SetAnimContainer(const std::vector<AnimationContainer*>& _animContainer);

		int GetCurrentClipIndex(int _containerIndex = 0) { return mFrameContainer[_containerIndex]->frameInfo.clipIndex; }

	private:
		std::vector<AnimationContainer*> mAnimContainer;
		std::vector<FrameContainer*>	 mFrameContainer;
		shared_ptr<Material>			 mpComputeMaterial;
	};
}


