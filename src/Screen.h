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
	Screen(NativeAdapter* nativeAdapter, const std::string screenName)
			: _nativeAdapter(nativeAdapter)
			, _screenName(screenName)
	{
	}

	virtual ~Screen() = default;

	void onEnter()
	{
		_nativeAdapter->onStartScreen(this);
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

	NativeAdapter* getNativeAdapter()
	{
		return _nativeAdapter;
	}

protected:

	void registerComponent(const std::string& name, Component* component)
	{
		_registredComponents[name] = component;
	}

private:
	std::string _screenName;
	NativeAdapter* _nativeAdapter;
	std::map<std::string, Component*> _registredComponents;
};
