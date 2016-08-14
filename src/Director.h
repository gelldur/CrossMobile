//
// Created by pingu on 1/14/16.
//

#pragma once

#include <map>
#include <memory>
#include <cassert>

#include <screen/Screen.h>

class Application;

class Director
{
public:
	using ScreenPtr = std::unique_ptr<Screen>;

	Director(Director const&) = delete;
	void operator=(Director const&) = delete;

	~Director() = default;

	static Director& getInstance()
	{
		assert(_instance != nullptr);
		return *_instance;
	}

	static void create(std::unique_ptr<Application> app);
	static void destroy();

	void pushScreen(Screen* screen);
	void pushScreen(const std::string& screenName, std::unique_ptr<Screen>&& screen);

	void popScreen(const std::string& screenName);

	void onCreateScreen(const std::string& screenName);
	void onResumeScreen(const std::string& screenName);
	void onPauseScreen(const std::string& screenName);
	void onDestroyScreen(const std::string& screenName);

	void onTickUI();

	Screen* findScreen(const std::string& screenName);

	Screen& getScreen(const std::string& screenName);

	Application* getApp() const
	{
		assert(_app != nullptr);
		return _app.get();
	}

private:
	static std::unique_ptr<Director> _instance;
	Director(std::unique_ptr<Application> app);

	Screen* _activeScreen = nullptr;
	std::unique_ptr<Application> _app;
	std::map<std::string, ScreenPtr> _screens;
};


