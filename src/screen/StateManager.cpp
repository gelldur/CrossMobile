//
// Created by Dawid Drozd aka Gelldur on 5/24/16.
//

#include "StateManager.h"

#include "log.h"
#include "Screen.h"

namespace StateManager
{

bool onEnter(Screen* screen)
{
	if (screen->getState() == Screen::State::EXIT)
	{
		screen->setState(Screen::State::ENTER);
		DLOG("%s::onEnter", screen->getName().c_str());
		screen->onEnter();
		return true;
	}
	return false;
}

bool onExit(Screen* screen)
{
	if (screen->getState() == Screen::State::DESTROY || screen->getState() == Screen::State::ENTER)
	{
		screen->setState(Screen::State::EXIT);
		DLOG("%s::onExit", screen->getName().c_str());
		screen->onExit();
		return true;
	}
	return false;
}

bool onCreate(Screen* screen)
{
	if (screen->getState() == Screen::State::ENTER || screen->getState() == Screen::State::DESTROY)
	{
		screen->setState(Screen::State::CREATE);
		DLOG("%s::onCreate", screen->getName().c_str());
		screen->onCreate();
		return true;
	}
	return false;
}

bool onResume(Screen* screen)
{
	if (willResume(screen))
	{
		screen->setState(Screen::State::RESUME);
		DLOG("%s::onResume", screen->getName().c_str());
		screen->onResume();
		return true;
	}
	return false;
}

bool willResume(Screen* screen)
{
	return screen->getState() == Screen::State::CREATE || screen->getState() == Screen::State::PAUSE;
}

bool onPause(Screen* screen)
{
	if (screen->getState() == Screen::State::RESUME)
	{
		screen->setState(Screen::State::PAUSE);
		DLOG("%s::onPause", screen->getName().c_str());
		screen->onPause();
		return true;
	}
	return false;
}

bool onDestroy(Screen* screen)
{
	if (screen->getState() == Screen::State::CREATE || screen->getState() == Screen::State::PAUSE)
	{
		screen->setState(Screen::State::DESTROY);
		DLOG("%s::onDestroy", screen->getName().c_str());
		screen->onDestroy();
		return true;
	}
	return false;
}

}
