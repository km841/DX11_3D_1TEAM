#pragma once

namespace hm
{
	struct SoundInfo
	{
		FMOD::Sound* pSound;
		bool bLoop;
		class Scene* pScene;
		std::list<FMOD::Channel*> ChannelList;
	};

	class SoundManager
	{
		DECLARE_SINGLE(SoundManager);

	public:
		void Initialize();
		void Update();
		void Destroy();

	public:
		FMOD::System* GetSoundSystem() const;

		bool LoadSound(const std::wstring& _strName, class Scene* _pScene,
			bool _bLoop, const string& _pFileName);

		void Play(const std::wstring& _strName);
		void Play(SoundInfo* _pSound);

		void Stop(const std::wstring& _strName);
		void Stop(SoundInfo* _pSound);

		void DeleteSound(class Scene* _pScene);

		SoundInfo* FindSound(const std::wstring& _strName);

	private:
		FMOD::System* mpSystem;
		std::unordered_map<std::wstring, SoundInfo*> mSoundMap;


	};
}


