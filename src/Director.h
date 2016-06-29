//
// Created by pingu on 1/14/16.
//

#pragma once

#include <map>
#include <memory>
#include <cassert>

class Application;

class Screen;

class Director
{
public:
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

	void pushScreen(const std::string& screenName, Screen* screen);
	void popScreen(const std::string& screenName);

	void onCreateScreen(const std::string& screenName);
	void onResumeScreen(const std::string& screenName);
	void onPauseScreen(const std::string& screenName);
	void onDestroyScreen(const std::string& screenName);

	void onTickUI();

	Screen* findScreen(const std::string& screenName);

	Application* getApp() const
	{
		return _app.get();
	}

private:
	static std::unique_ptr<Director> _instance;
	Director(std::unique_ptr<Application> app);

	Screen* _activeScreen = nullptr;
	std::unique_ptr<Application> _app;
	std::map<std::string, Screen*> _screens;
};


