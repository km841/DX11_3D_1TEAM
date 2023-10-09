#include "pch.h"
#include "SoundManager.h"


namespace hm
{
	SoundManager::SoundManager()
	{

	}

	SoundManager::~SoundManager()
	{
		std::unordered_map<std::wstring, SoundInfo*>::iterator Iter = mSoundMap.begin();
		std::unordered_map<std::wstring, SoundInfo*>::iterator EndIter = mSoundMap.end();

		for (; Iter != EndIter; ++Iter)
		{
			Iter->second->pSound->release();
			SAFE_DELETE(Iter->second);
		}

		mSoundMap.clear();

		if (nullptr != mpSystem)
		{
			mpSystem->close();
			mpSystem->release();
		}
	}

	void SoundManager::Initialize()
	{
		// System 생성
		FMOD::System_Create(&mpSystem);

		// 시스템 초기화 init(채널 갯수, 초가화 방식, 다른 드라이버)
		mpSystem->init(FMOD_MAX_CHANNEL_WIDTH, FMOD_INIT_NORMAL, nullptr);
	}

	void SoundManager::Update()
	{
		std::unordered_map<std::wstring, SoundInfo*>::iterator Iter = mSoundMap.begin();
		std::unordered_map<std::wstring, SoundInfo*>::iterator EndIter = mSoundMap.end();

		for (; Iter != EndIter; ++Iter)
		{
			std::list<FMOD::Channel*>::iterator ChannelIter = Iter->second->ChannelList.begin();
			std::list<FMOD::Channel*>::iterator ChannelEndIter = Iter->second->ChannelList.end();

			for (; ChannelIter != ChannelEndIter;)
			{
				bool bIsplay = false;
				(*ChannelIter)->isPlaying(&bIsplay);

				if (false == bIsplay)
				{
					ChannelIter = Iter->second->ChannelList.erase(ChannelIter);
					ChannelIter = Iter->second->ChannelList.end();
				}
				else
				{
					++ChannelIter;
				}
			}
		}
	}

	void SoundManager::Destroy()
	{
	}

	FMOD::System* SoundManager::GetSoundSystem() const
	{
		return nullptr;
	}

	bool SoundManager::LoadSound(const std::wstring& _strName, Scene* _pScene, bool _bLoop, const string& _pFileName)
	{
		SoundInfo* pInfo = FindSound(_strName);
		if (nullptr != pInfo)
			return false;

		pInfo = new SoundInfo;
		pInfo->bLoop = _bLoop;

		FMOD_MODE eMode = FMOD_LOOP_NORMAL;			// 반복

		if (false == _bLoop)
			eMode = FMOD_DEFAULT;					// 한번

		if (FMOD_OK != mpSystem->createSound(_pFileName.c_str(), eMode, nullptr, &pInfo->pSound))
		{
			SAFE_DELETE(pInfo);
			AssertEx(false, L"SoundManager::LoadSound() - Sound 로드 실패");
		}
		
		pInfo->pScene = _pScene;
		mSoundMap.insert(std::make_pair(_strName, pInfo));

		return true;
	}

	void SoundManager::Play(const std::wstring& _strName)
	{
		SoundInfo* pSoundInfo = FindSound(_strName);

		// 없으면 return
		if (nullptr == pSoundInfo)
			return;

		FMOD::Channel* pChannel = nullptr;
		mpSystem->playSound(pSoundInfo->pSound, nullptr, false, &pChannel);

		pSoundInfo->ChannelList.push_back(pChannel);
	}

	void SoundManager::Play(SoundInfo* _pSound)
	{
		FMOD::Channel* pChannel = nullptr;
		mpSystem->playSound(_pSound->pSound, nullptr, false, &pChannel);

		_pSound->ChannelList.push_back(pChannel);
	}

	void SoundManager::Stop(const std::wstring& _strName)
	{
		SoundInfo* pSoundInfo = FindSound(_strName);

		if (nullptr == pSoundInfo)
		{
			return;
		}

		std::list<FMOD::Channel*>::iterator Iter = pSoundInfo->ChannelList.begin();
		std::list<FMOD::Channel*>::iterator EndIter = pSoundInfo->ChannelList.end();

		for (; Iter != EndIter; ++Iter)
		{
			(*Iter)->stop();
		}

		pSoundInfo->ChannelList.clear();
	}

	void SoundManager::Stop(SoundInfo* _pSound)
	{
		if (nullptr == _pSound)
		{
			return;
		}

		std::list<FMOD::Channel*>::iterator Iter = _pSound->ChannelList.begin();
		std::list<FMOD::Channel*>::iterator EndIter = _pSound->ChannelList.end();

		for (; Iter != EndIter; ++Iter)
		{
			(*Iter)->stop();
		}

		_pSound->ChannelList.clear();
	}

	void SoundManager::DeleteSound(Scene* _pScene)
	{
		std::unordered_map<std::wstring, SoundInfo*>::iterator Iter = mSoundMap.begin();
		std::unordered_map<std::wstring, SoundInfo*>::iterator EndIter = mSoundMap.end();

		for (; Iter != EndIter;)
		{
			if (Iter->second->pScene == _pScene)
			{
				Iter->second->pSound->release();
				SAFE_DELETE(Iter->second);
				Iter = mSoundMap.erase(Iter);
			}
			else
			{
				++Iter;
			}
		}
	}

	SoundInfo* SoundManager::FindSound(const std::wstring& _strName)
	{
		std::unordered_map<std::wstring, SoundInfo*>::iterator Iter = mSoundMap.find(_strName);

		if (Iter == mSoundMap.end())
		{
			return nullptr;
		}

		return Iter->second;
	}
}

