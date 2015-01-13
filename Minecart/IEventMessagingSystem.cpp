#include "stdafx.h"
#include "IEventMessagingSystem.h"
#include "EventMessagingSystem.h"

namespace model {

	EventMessagingSystem& IEventMessagingSystem::ems_ = EventMessagingSystem::getInstance();

	IEventMessagingSystem::IEventMessagingSystem()
	{

	}

	IEventMessagingSystem::~IEventMessagingSystem()
	{

	}

	void IEventMessagingSystem::Register(EEvent eEvent, IEventMessagingSystem* pObj, Callback pFunc)
	{
		ems_.Register(eEvent, pObj, pFunc);
	}

	void IEventMessagingSystem::UnRegister(EEvent eEvent, IEventMessagingSystem* pObj, Callback pFunc)
	{
		ems_.UnRegister(eEvent, pObj, pFunc);
	}

	void IEventMessagingSystem::Post(EEvent eEvent, void* pData, unsigned int uiSize)
	{
		ems_.Post(eEvent, pData, uiSize);
	}

}
