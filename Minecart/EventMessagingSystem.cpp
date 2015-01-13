#include "stdafx.h"
#include "EventMessagingSystem.h"

namespace model {

	EventMessagingSystem::EventMessagingSystem()
	{

	}

	void EventMessagingSystem::clearAll()
	{
		for (int i = 0; i < EEvent::COUNT; ++i)
			events_[i].clear();
	}

	int EventMessagingSystem::eventCount(EEvent eEvent)
	{
		return events_[eEvent].size();
	}

	void EventMessagingSystem::Post(EEvent eEvent, void* pData, unsigned int uiSize)
	{
		for (std::vector<EveCall>::iterator it = events_[eEvent].begin(); it != events_[eEvent].end(); ++it)
		{
			IEventMessagingSystem& e = *(*it).pObj;
			Callback call = (*it).pFunc;
			(e.*call)(pData);
		}
	}

	void EventMessagingSystem::Register(EEvent eEvent, IEventMessagingSystem* pObj, Callback pFunc)
	{
		EveCall ec = { pObj, pFunc };
		events_[eEvent].push_back(ec);
	}

	void EventMessagingSystem::UnRegister(EEvent eEvent, IEventMessagingSystem* pObj, Callback pFunc)
	{
		for (std::vector<EveCall>::iterator it = events_[eEvent].begin(); it != events_[eEvent].end(); ++it)
		{
			if ((*it).pObj == pObj && (*it).pFunc == pFunc)
			{
				events_[eEvent].erase(it);
				return;
			}
		}
	}

	EventMessagingSystem& EventMessagingSystem::getInstance()
	{
		static EventMessagingSystem instance;
		return instance;
	}

}