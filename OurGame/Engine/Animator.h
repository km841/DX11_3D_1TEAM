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
		void Play(int _idx);

		void SetBones(const std::vector<BoneInfo>* _bones);
		void SetAnimClip(const std::vector<AnimClipInfo>* _animClips);
		void PushData();

		int GetAnimCount() { return static_cast<UINT32>(animClips->size()); }
		int GetCurrentClipIndex() { return clipIndex; }

	private:
		const std::vector<BoneInfo>* bones;
		const std::vector<AnimClipInfo>* animClips;

		float	updateTime = 0.f;
		int		clipIndex = 0;
		int		frame = 0;
		int		nextFrame = 0;
		float	frameRatio = 0;
		shared_ptr<StructuredBuffer>	pBoneFinalMatrix; 
		shared_ptr<Material>			 mpComputeMaterial;
		bool							bBoneFinalUpdated = false;
	};
}


