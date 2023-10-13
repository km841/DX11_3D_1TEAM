#pragma once
#include "Component.h"

namespace hm
{
	class AudioSound :
		public Component
	{
	public:
		AudioSound();
		virtual ~AudioSound();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual Component* Clone(GameObject* _pGameObject);

	public:
		void SetSound(const std::wstring& _strName);
		void SetSound(const std::wstring& _strName, class Scene* _pScene,
			bool _bLoop, const string& _pFileName);

		void EnableBGM(bool _Enable);

		void Play(int _volume = 100);
		void Stop();
		void Pause();


	private:
		std::wstring	  mFileName;
		struct SoundInfo* mpSoundInfo;
		FMOD::Channel*    mpChannel;
		bool			  mbBGM;
		bool			  mbLoop;
		bool			  mbPlay;
		float Volume;
	};
}


