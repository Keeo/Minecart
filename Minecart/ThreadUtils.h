#pragma once

#include <Windows.h>
#include <assert.h>
#include <iostream>

#include "ThreadPool.h"

namespace utils
{
	// https://msdn.microsoft.com/en-us/library/windows/desktop/ms686277(v=vs.85).aspx
	enum ThreadPriority{
		LOW = -2,
		NORMAL = 0,
		HIGH = 2
	};

	class ThreadUtils
	{
		ThreadUtils();
		~ThreadUtils();
	public:
		
		static void setThreadPriority(ThreadPriority priority, HANDLE hThread = GetCurrentThread()) {
			int currentPriority = GetThreadPriority(hThread);
			std::cout << "Current thread priority: " << currentPriority << " setting:" << priority << std::endl;
			BOOL ret = SetThreadPriority(hThread, priority);
			assert(ret);
			assert(GetThreadPriority(hThread) == priority);
		}

		static void setThreadPoolPriority(ThreadPool* tp, ThreadPriority priority = LOW)
		{
			int threads = tp->size();
			for (int i = 0; i < threads; ++i) {
				HANDLE hThread = tp->get_thread(i).native_handle();
				setThreadPriority(priority, hThread);
			}
		}

	};

}
