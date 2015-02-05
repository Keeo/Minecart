// Minecart.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Controller.h"
#include "Chunk.h"
#include "Window.h"
#include <glm/gtc/noise.hpp>
#include <glm/gtx/string_cast.hpp>
#include "ThreadUtils.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//utils::ThreadUtils::setThreadPriority(utils::ThreadPriority::HIGH);
	Controller* c = new Controller();
	c->run();
	return 0;
}

