//
// Created by Dawid Drozd aka Gelldur on 05.02.16.
//

#include "Application.h"

#include <log.h>
#include <Director.h>
#include <component/ComponentSerializer.h>

#include <Poco/Path.h>

Application::Application(CrossMobile::Platform::Bridge* bridge, ScreenCreator* screenCreator)
		: _preferences(Poco::Path(bridge->getWritablePath()).append("prefs.db").toString())
		, _bridge(bridge)
		, _screenCreator(screenCreator)
{
	DLOG("PATH: %s", bridge->getWritablePath().c_str());
	ComponentSerializer::init();
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

CrossMobile::Platform::Bridge& Application::getBridge()
{
	if (_bridge)
	{
		return *_bridge;
	}
	throw std::runtime_error("Bridge is not set!");
}

const std::unique_ptr<ScreenCreator>& Application::getScreenCreator() const
{
	return _screenCreator;
}
