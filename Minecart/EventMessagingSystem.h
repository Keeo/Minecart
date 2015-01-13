#pragma once

#include "IEventMessagingSystem.h"
#include "EEvent.h"
#include <unordered_map>
#include <vector>

namespace model {

	struct EveCall
	{
		IEventMessagingSystem * pObj;
		Callback pFunc;
	};


	class EventMessagingSystem
	{
	public:
		static EventMessagingSystem& getInstance();
		void Post(EEvent eEvent, void * pData = 0, unsigned int uiSize = 0);
		void Register(EEvent eEvent, IEventMessagingSystem * pObj, Callback pFunc);
		void UnRegister(EEvent eEvent, IEventMessagingSystem * pObj, Callback pFunc);
		int eventCount(EEvent eEvent);
		void clearAll();
	private:

		std::vector<EveCall> events_[EEvent::COUNT];

		EventMessagingSystem();
		EventMessagingSystem(EventMessagingSystem const&);
		void operator=(EventMessagingSystem const&);
	};

}

