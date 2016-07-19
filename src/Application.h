//
// Created by Dawid Drozd aka Gelldur on 05.02.16.
//

#pragma once

#include <string>
#include <api/ApiThreadPool.h>
#include <data/Preferences.h>

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

	Preferences& getPreferences()
	{
		return _preferences;
	}

	static Application* getInstance();
private:
	UILoop _uiLoop;
	ApiThreadPool _apiThreadPool;
	Preferences _preferences;
};


