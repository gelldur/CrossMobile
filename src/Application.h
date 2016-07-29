//
// Created by Dawid Drozd aka Gelldur on 05.02.16.
//

#pragma once

#include <string>
#include <memory>

#include <api/ApiThreadPool.h>
#include <data/Preferences.h>
#include <platform/Bridge.h>

#include "UILoop.h"

class Application
{
public:
	Application(CrossMobile::Platform::Bridge* bridge);
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

	CrossMobile::Platform::Bridge& getBridge();

	static Application* getInstance();
private:
	UILoop _uiLoop;
	ApiThreadPool _apiThreadPool;
	Preferences _preferences;
	std::unique_ptr<CrossMobile::Platform::Bridge> _bridge;
};
