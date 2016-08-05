//
// Created by pingu on 1/14/16.
//
#include "Director.h"

#include <log.h>
#include <screen/StateManager.h>
#include <exception/Fail.h>

#include "screen/Screen.h"
#include "Application.h"

std::unique_ptr<Director> Director::_instance = nullptr;

Director::Director(std::unique_ptr<Application> app)
		: _app{std::move(app)}
{
}

void Director::create(std::unique_ptr<Application> app)
{
	if (_instance != nullptr)
	{
		WLOG("Creating new app? Probably you want release previous app instance.\nDon't worry i will handle that!");
		destroy();
	}
	_instance = std::unique_ptr<Director>(new Director(std::move(app)));
	_instance->_app->onCreate();
}

void Director::destroy()
{
	_instance.reset();
}

void Director::pushScreen(const std::string& screenName, std::unique_ptr<Screen> screen)
{
	DLOG("Director: pushScreen(%s)", screenName.c_str());

	auto& previousScreen = _screens[screenName];
	if (previousScreen != nullptr)
	{
		Fail(__FILE__, __func__, __LINE__).add("Screen already exist:").add(screenName).report();
		return;
	}
	previousScreen = std::move(screen);

	StateManager::onEnter(previousScreen.get());
}

void Director::onCreateScreen(const std::string& screenName)
{
	auto screen = findScreen(screenName);
	if (screen == nullptr)
	{
		Fail(__FILE__, __func__, __LINE__).add("No such screen:").add(screenName).report();
		return;
	}

	StateManager::onCreate(screen);
}

void Director::onResumeScreen(const std::string& screenName)
{
	auto screen = findScreen(screenName);
	if (screen == nullptr)
	{
		Fail(__FILE__, __func__, __LINE__).add("No such screen:").add(screenName).report();
		return;
	}

	if (StateManager::willResume(screen))
	{
		if (_activeScreen != nullptr)
		{
			StateManager::onPause(_activeScreen);
		}

		_activeScreen = screen;
		StateManager::onResume(screen);
	}
}

void Director::onPauseScreen(const std::string& screenName)
{
	auto screen = findScreen(screenName);
	if (screen == nullptr)
	{
		Fail(__FILE__, __func__, __LINE__).add("No such screen:").add(screenName).report();
		return;
	}
	if (StateManager::onPause(screen))
	{
		_activeScreen = nullptr;
	}
}

void Director::onDestroyScreen(const std::string& screenName)
{
	auto findScreen = _screens.find(screenName);
	if (findScreen == _screens.end())
	{
		Fail(__FILE__, __func__, __LINE__).add("No such screen:").add(screenName).report();
		return;
	}

	auto screen = std::move(findScreen->second);

	StateManager::onDestroy(screen.get());
	_screens.erase(findScreen);
	StateManager::onExit(screen.get());
}

void Director::popScreen(const std::string& screenName)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

Screen* Director::findScreen(const std::string& screenName)
{
	auto findScreen = _screens.find(screenName);
	if (findScreen == _screens.end())
	{
		FLOG("No such screen %s", screenName.c_str());
		DLOG("%s:%s:%d", __FILE__, __func__, __LINE__);
		return nullptr;
	}
	return findScreen->second.get();
}

Screen& Director::getScreen(const std::string& screenName)
{
	auto screen = findScreen(screenName);
	if (screen == nullptr)
	{
		Fail(__FILE__, __func__, __LINE__).add("No such screen:").add(screenName).report();
	}
	return *screen;
}

void Director::onTickUI()
{
	_app->getUILoop().onTick();
}
