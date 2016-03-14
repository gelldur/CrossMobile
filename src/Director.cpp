//
// Created by pingu on 1/14/16.
//

#include <log.h>
#include <assert.h>
#include "Director.h"

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
	screen->onEnter();
}

void Director::onCreateScreen(const std::string& screenName)
{
	DLOG("Director: onCreateScreen(%s)", screenName.c_str());
	auto screen = findScreen(screenName);
	if (screen == nullptr)
	{
		return;
	}
	screen->onCreate();
}

void Director::onResumeScreen(const std::string& screenName)
{
	DLOG("Director: onResumeScreen(%s)", screenName.c_str());
	auto screen = findScreen(screenName);
	if (screen == nullptr)
	{
		return;
	}
	screen->onResume();
}

void Director::onPauseScreen(const std::string& screenName)
{
	DLOG("Director: onPauseScreen(%s)", screenName.c_str());
	auto screen = findScreen(screenName);
	if (screen == nullptr)
	{
		return;
	}
	screen->onPause();
}

void Director::onDestroyScreen(const std::string& screenName)
{
	DLOG("Director: onDestroyScreen(%s)", screenName.c_str());
	auto screen = findScreen(screenName);
	if (screen == nullptr)
	{
		return;
	}
	screen->onDestroy();
	_screens.erase(screenName);
	screen->onExit();
	delete screen;
}

void Director::popScreen(const std::string& screenName)
{

}


void Director::onStartApplication(Application* app)
{
	if (_app != nullptr)
	{
		//TODO throw exceptions
		FLOG("App already created!");
	}
	_app = app;
	app->onCreate();
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
