#pragma once

namespace hm
{
	class SemaphoreSync
	{
		SemaphoreSync(HANDLE* _semaphore)
		{
			mSemaphore = _semaphore;
			WaitForSingleObject(*mSemaphore, INFINITE);
		}

		~SemaphoreSync()
		{
			ReleaseSemaphore(*mSemaphore, 1, NULL);
		}

	private:
		HANDLE* mSemaphore;
	};
}


