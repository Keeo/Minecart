#pragma once

#include "EEvent.h"

namespace model
{

	class IEventMessagingSystem;
	class EventMessagingSystem;
	typedef void (IEventMessagingSystem::*Callback)(void *pData);

	class IEventMessagingSystem
	{
	public:
		IEventMessagingSystem();
		~IEventMessagingSystem();

		void Register(EEvent eEvent, IEventMessagingSystem * pObj, Callback pFunc);

		void UnRegister(EEvent eEvent, IEventMessagingSystem * pObj, Callback pFunc);

		void Post(EEvent eEvent, void * pData, unsigned int uiSize);

	protected:
		static EventMessagingSystem& ems_;
	};

}

