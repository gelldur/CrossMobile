//
// Created by Dawid Drozd aka Gelldur on 05.02.16.
//

#pragma once

#include <string>
#include <api/ApiThreadPool.h>

#include "UILoop.h"

class Application
{
public:
	Application();
	virtual ~Application() = default;

	virtual void onCreate();

	virtual void startScreen(const std::string& screenName);

	UILoop& getUILoop()
	{
		return _uiLoop;
	}

	ApiThreadPool& getApiThreadPool()
	{
		return _apiThreadPool;
	}

	static Application* getInstance()
	{
		return _instance;
	}

private:
	static Application* _instance;

	UILoop _uiLoop;
	ApiThreadPool _apiThreadPool;
};


