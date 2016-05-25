//
// Created by pingu on 1/14/16.
//

#pragma once

#include <string>
#include <map>
#include <functional>

#include <log.h>
#include <bridge/NativeAdapter.h>

#include "Component.h"

class Screen
{
public:
	Screen(const std::string screenName)
			: _screenName(screenName)
	{
	}

	virtual ~Screen() = default;

	void onEnter()
	{
	}

	void onExit()
	{
	}

	virtual void onCreate() = 0;

	virtual void onResume() = 0;

	virtual void onPause() = 0;

	virtual void onDestroy() = 0;

	const std::string& getName() const
	{
		return _screenName;
	}

	Component* findComponent(const std::string& name)
	{
		if (_registredComponents.find(name) == _registredComponents.end())
		{
			FLOG("No such component %s", name.c_str());
			return nullptr;
		}
		return _registredComponents[name];
	}

	enum State
	{
		EXIT = 0, ENTER = 1, CREATE = 3, RESUME = 7, PAUSE = 8, DESTROY = 11
	};

	void setState(State state)
	{
		_state = state;
	}

	State getState() const
	{
		return _state;
	}

protected:

	void registerComponent(const std::string& name, Component* component)
	{
		_registredComponents[name] = component;
	}

private:
	State _state = EXIT;
	std::string _screenName;
	std::map<std::string, Component*> _registredComponents;
};
