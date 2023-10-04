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
		void Play(int _idx, bool _bLoop);
		void Play(const wstring& _animName, bool _bLoop);
		int FindAnimationIndex(const wstring& _animName);

		void SetBones(std::vector<BoneInfo>* _bones);
		void SetAnimClip(std::vector<AnimClipInfo>* _animClidwps);
		std::vector<AnimClipInfo>* GetAnimClip() { return mAnimClips; }
		void PushData();

		int GetAnimCount() { return static_cast<UINT32>(mAnimClips->size()); }
		int GetCurrentClipIndex() { return mClipIndex; }
		double GetFrameRatio() { return mUpdateTime / (*mAnimClips)[mClipIndex].duration; }

		void RenameAnimation(const wstring& _orgName, const wstring& _newName);
		void RenameAnimation(int _index, const wstring& _newName);

		void SetLoop(const wstring& _animName, bool _bFlag);
		void SetLoop(int _index, bool _bFlag);

		void SetHasExitFlag(const wstring& _animName, bool _bFlag);
		void SetHasExitFlag(int _index, bool _bFlag);

		bool IsFinished() { return mbIsFinished; }

		void SetPlaySpeed(const wstring& _animName, float _playSpeed);
		void SetPlaySpeed(int _index, float _playSpeed);

		wstring GetCurrentClipName() { return (*mAnimClips)[mClipIndex].animName; }

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
		int								mAfterFrame;
		bool							mAfterLoop;
	};
}


