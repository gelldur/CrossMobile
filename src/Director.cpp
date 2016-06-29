//
// Created by pingu on 1/14/16.
//
#include "Director.h"

#include <log.h>
#include <screen/StateManager.h>

#include "Screen.h"
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

void Director::pushScreen(const std::string& screenName, Screen* screen)
{
	DLOG("Director: pushScreen(%s)", screenName.c_str());

	auto previousScreen = _screens[screenName];
	if (previousScreen != nullptr)
	{
		ELOG("Screen already exist: %s", screenName.c_str());
		return;
	}

	_screens[screenName] = screen;

	StateManager::onEnter(screen);
}

void Director::onCreateScreen(const std::string& screenName)
{
	DLOG("Director: onCreateScreen(%s)", screenName.c_str());
	auto screen = findScreen(screenName);
	if (screen == nullptr)
	{
		return;
	}

	StateManager::onCreate(screen);
}

void Director::onResumeScreen(const std::string& screenName)
{
	DLOG("Director: onResumeScreen(%s)", screenName.c_str());
	auto screen = findScreen(screenName);
	if (screen == nullptr)
	{
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
	DLOG("Director: onPauseScreen(%s)", screenName.c_str());
	auto screen = findScreen(screenName);
	if (screen == nullptr)
	{
		return;
	}
	if (StateManager::onPause(screen))
	{
		_activeScreen = nullptr;
	}
}

void Director::onDestroyScreen(const std::string& screenName)
{
	DLOG("Director: onDestroyScreen(%s)", screenName.c_str());
	auto screen = findScreen(screenName);
	if (screen == nullptr)
	{
		return;
	}
	StateManager::onDestroy(screen);
	_screens.erase(screenName);
	StateManager::onExit(screen);
	delete screen;
}

void Director::popScreen(const std::string& screenName)
{

}

Screen* Director::findScreen(const std::string& screenName)
{
	if (_screens.find(screenName) == _screens.end())
	{
		FLOG("No such screen %s", screenName.c_str());
		return nullptr;
	}
	return _screens[screenName];
}

void Director::onTickUI()
{
	_app->getUILoop().onTick();
}
