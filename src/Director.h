//
// Created by pingu on 1/14/16.
//

#pragma once

#include <map>
#include "Screen.h"
#include "Application.h"

class Director
{
public:
	Director(Director const&) = delete;
	void operator=(Director const&) = delete;

	static Director& getInstance()
	{
		static Director instance;
		return instance;
	}

	void pushScreen(const std::string& screenName, Screen* screen);
	void popScreen(const std::string& screenName);

	void onCreateScreen(const std::string& screenName);
	void onResumeScreen(const std::string& screenName);
	void onPauseScreen(const std::string& screenName);
	void onDestroyScreen(const std::string& screenName);

	void onStartApplication(Application* app);

	void onTickUI();

	Screen* findScreen(const std::string& screenName);

private:
	Director() = default;

	Application* _app;
	std::map<std::string, Screen*> _screens;
};


