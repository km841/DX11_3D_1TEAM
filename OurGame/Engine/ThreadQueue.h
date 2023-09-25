#pragma once
#include "SemaphoreSync.h"
namespace hm
{
	template<typename T, int SIZE = 200>
	class ThreadQueue
	{
	public:
		ThreadQueue()
		{
			mSize = 0;
			mHead = 0;
			mTail = 0;
			mCapacity = SIZE + 1;
			mSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
		}

		~ThreadQueue()
		{
			CloseHandle(mSemaphore);
		}

	public:
		void Push(const T& _data)
		{
			SemaphoreSync sync(&mSemaphore);

			int tail = (mTail + 1) % mCapacity;
			if (tail == mHead)
				return;

			mQueue[tail] = _data;
			mTail = tail;
			++mSize;
		}

		T& Front()
		{
			if (true == Empty())
				AssertEx(false, L"ThreadQueue::Front() - 비어있는 큐에 Front() 호출");

			SemaphoreSync sync(&mSemaphore);
			int head = (mHead + 1) % mCapacity;
			return mQueue[head];
		}

		void Pop()
		{
			if (true == Empty())
				AssertEx(false, L"ThreadQueue::Pop() - 비어있는 큐에 Pop() 호출");

			SemaphoreSync sync(&mSemaphore);
			mHead = (mHead + 1) % mCapacity;
			--mSize;
		}

		int Size()
		{
			return mSize;
		}

		bool Empty()
		{
			return mSize == 0;
		}

		void Clear()
		{
			SemaphoreSync sync(&mSemaphore);
			mHead = 0;
			mTail = 0;
			mSize = 0;
		}

	private:
		T mQueue[SIZE + 1];
		int mCapacity;
		int mSize;
		int mHead;
		int mTail;
		
		HANDLE mSemaphore;
	};
}


