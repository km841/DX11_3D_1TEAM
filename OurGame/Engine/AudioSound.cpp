#include "pch.h"
#include "AudioSound.h"
#include "SoundManager.h"
#include "GameObject.h"

namespace hm
{
	AudioSound::AudioSound()
		: Component(ComponentType::AudioSound)
		, mbLoop(false)
		, mbBGM(false)
		, mbPlay(false)
		, mpChannel(nullptr)
		, mpSoundInfo(nullptr)
	{
	}
	AudioSound::~AudioSound()
	{
	}
	void AudioSound::Initialize()
	{
		if (true == mbPlay)
		{
			if (nullptr != mpChannel)
			{
				mpChannel->stop();

				std::list<FMOD::Channel*>::iterator Iter = mpSoundInfo->ChannelList.begin();
				std::list<FMOD::Channel*>::iterator EndIter = mpSoundInfo->ChannelList.end();

				for (; Iter != EndIter; ++Iter)
				{
					if (*Iter == mpChannel)
					{
						mpSoundInfo->ChannelList.erase(Iter);
						break;
					}
				}

				mpChannel = nullptr;
			}

			GET_SINGLE(SoundManager)->Play(mpSoundInfo);

			mpChannel = mpSoundInfo->ChannelList.back();
		}
	}
	void AudioSound::Update()
	{
		if (true == mbPlay)
		{
			bool bIsPlay = false;
			mpChannel->isPlaying(&bIsPlay);

			if (false == bIsPlay)
			{
				mbPlay = false;
				mpChannel = nullptr;
			}

		}
	}

	Component* AudioSound::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new AudioSound);
	}
	void AudioSound::SetSound(const std::wstring& _strName)
	{
		mpSoundInfo = GET_SINGLE(SoundManager)->FindSound(_strName);

		mFileName = _strName;
	}
	void AudioSound::SetSound(const std::wstring& _strName, Scene* _pScene, bool _bLoop, const string& _pFileName)
	{
		if (false == GET_SINGLE(SoundManager)->LoadSound(_strName, _pScene, _bLoop, _pFileName))
		{
			return;
		}

		mpSoundInfo = GET_SINGLE(SoundManager)->FindSound(_strName);
		mFileName = _strName;
	}
	void AudioSound::EnableBGM(bool _Enable)
	{
		mbBGM = _Enable;
	}
	void AudioSound::Play()
	{
		//if (false == mbPlay)
		//{
		//	mpChannel->stop();

		//	std::list<FMOD::Channel*>::iterator Iter = mpSoundInfo->ChannelList.begin();
		//	std::list<FMOD::Channel*>::iterator EndIter = mpSoundInfo->ChannelList.end();

		//	for (; Iter != EndIter; ++Iter)
		//	{
		//		if (*Iter == mpChannel)
		//		{
		//			mpSoundInfo->ChannelList.erase(Iter);
		//			break;
		//		}
		//	}

		//	mpChannel = nullptr;
		//}

		//mbPlay = true;
		//GET_SINGLE(SoundManager)->Play(mpSoundInfo);

		//mpChannel = mpSoundInfo->ChannelList.back();
	}
	void AudioSound::Stop()
	{
		if (true == mbPlay)
		{
			mpChannel->stop();

			std::list<FMOD::Channel*>::iterator Iter = mpSoundInfo->ChannelList.begin();
			std::list<FMOD::Channel*>::iterator EndIter = mpSoundInfo->ChannelList.end();

			for (; Iter != EndIter; ++Iter)
			{
				if (*Iter == mpChannel)
				{
					mpSoundInfo->ChannelList.erase(Iter);
					break;
				}
			}
		}
	}
	void AudioSound::Pause()
	{
	}
}