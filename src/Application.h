//
// Created by Dawid Drozd aka Gelldur on 05.02.16.
//

#pragma once

#include <string>
#include <bridge/NativeAdapter.h>
#include <api/ApiThreadPool.h>

#include "UILoop.h"

class Application
{
public:
	Application(NativeAdapter* nativeAdapter);
	~Application() = default;

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

protected:
	NativeAdapter* getNativeAdapter() const
	{
		return _nativeAdapter;
	}

private:
	static Application* _instance;
	NativeAdapter* _nativeAdapter;
	UILoop _uiLoop;
	ApiThreadPool _apiThreadPool;
};


