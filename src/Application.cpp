//
// Created by Dawid Drozd aka Gelldur on 05.02.16.
//

#include "Application.h"

#include <log.h>
#include <Director.h>

Application::Application()
{
}

void Application::onCreate()
{
	DLOG("Application onCreate");
}

void Application::startScreen(const std::string& screenName)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

Application* Application::getInstance()
{
	assert(Director::getInstance().getApp() != nullptr);
	return Director::getInstance().getApp();
}


