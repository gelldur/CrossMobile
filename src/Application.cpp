//
// Created by Dawid Drozd aka Gelldur on 05.02.16.
//

#include <log.h>
#include "Application.h"

Application::Application(NativeAdapter* nativeAdapter)
		: _nativeAdapter(nativeAdapter)
{
}

void Application::onCreate()
{
	DLOG("Application onCreate");
}

void Application::startScreen(const std::string& screenName)
{
}
