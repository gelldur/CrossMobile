//
// Created by Dawid Drozd aka Gelldur on 05.02.16.
//

#include <log.h>
#include "Application.h"

Application* Application::_instance = nullptr;

Application::Application(NativeAdapter* nativeAdapter)
		: _nativeAdapter(nativeAdapter)
{
	_instance = this;
}

void Application::onCreate()
{
	DLOG("Application onCreate");
}

void Application::startScreen(const std::string& screenName)
{
}
