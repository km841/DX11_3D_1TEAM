#pragma once

namespace hm
{
	class ThreadBase
	{
	protected:
		ThreadBase();
		virtual ~ThreadBase() = 0;

	public:
		virtual void Initialize();
		virtual void Run() = 0;

	public:
		void Start();
		void Pause();
		void Resume();

		void SetLoop(bool _bLoop) { mbLoop = _bLoop; }

	private:
		void WaitStartEvent();
		static UINT32 __stdcall ThreadFunction(void* _pArg);

	public:
		template<typename T>
		static T* CreateThread(const string& _name)
		{
			T* pThread = new T;

			pThread->mName = _name;
			pThread->Initialize();

			return pThread;
		}

	private:
		string mName;
		HANDLE mThreadHandle;
		HANDLE mStartEvent;

	protected:
		bool mbLoop;

	};
}


