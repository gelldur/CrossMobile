//
// Created by Dawid Drozd aka Gelldur on 05.02.16.
//

#include "Application.h"

#include <cassert>

#include <log.h>

Application* Application::_instance = nullptr;

Application::Application()
{
	assert(_instance == nullptr && "Fix me ;)");
	_instance = this;
}

void Application::onCreate()
{
	DLOG("Application onCreate");
}

void Application::startScreen(const std::string& screenName)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}
