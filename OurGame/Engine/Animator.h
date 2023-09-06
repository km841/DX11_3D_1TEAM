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
		void Play(const wstring& _animName);
		int FindAnimationIndex(const wstring& _animName);

		void SetBones(std::vector<BoneInfo>* _bones);
		void SetAnimClip(std::vector<AnimClipInfo>* _animClips);
		void PushData();

		int GetAnimCount() { return static_cast<UINT32>(mAnimClips->size()); }
		int GetCurrentClipIndex() { return mClipIndex; }
		float GetFrameRatio() { return mFrameRatio; }

		void SetHasExitFlag(bool _bFlag) { mbHasExit = _bFlag; }

		void RenameAnimation(const wstring& _orgName, const wstring& _newName);
		void RenameAnimation(int _index, const wstring& _newName);

		void SetLoop(const wstring& _animName, bool _bFlag);
		void SetLoop(int _index, bool _bFlag);

		bool IsFinished() { return mbIsFinished; }

	private:
		std::vector<BoneInfo>*			mBones;
		std::vector<AnimClipInfo>*		mAnimClips;

		float							mUpdateTime = 0.f;
		int								mClipIndex = 0;
		int								mFrame = 0;
		int								mNextFrame = 0;
		float							mFrameRatio = 0;
		shared_ptr<StructuredBuffer>	mpBoneFinalMatrix; 
		shared_ptr<Material>			mpComputeMaterial;
		bool							mbBoneFinalUpdated = false;
		bool							mbIsFinished;

		bool							mbHasExit;
		int								mAfterFrame;
	};
}


