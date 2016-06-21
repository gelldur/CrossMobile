//
// Created by pingu on 1/14/16.
//

#pragma once

#include <map>
#include "Screen.h"
class Application;

class Director
{
public:
	Director(Director const&) = delete;
	void operator=(Director const&) = delete;

	~Director();

	static Director& getInstance()
	{
		assert(_instance != nullptr);
		return *_instance;
	}

	static void create();
	static void destroy();

	void pushScreen(const std::string& screenName, Screen* screen);
	void popScreen(const std::string& screenName);

	void onCreateScreen(const std::string& screenName);
	void onResumeScreen(const std::string& screenName);
	void onPauseScreen(const std::string& screenName);
	void onDestroyScreen(const std::string& screenName);

	void onStartApplication(Application* app);

	void onTickUI();

	Screen* findScreen(const std::string& screenName);

	Application* getApp() const
	{
		return _app;
	}

private:
	static Director* _instance;
	Director() = default;

	Application* _app = nullptr;
	Screen* _activeScreen = nullptr;
	std::map<std::string, Screen*> _screens;
};


