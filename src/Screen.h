//
// Created by pingu on 1/14/16.
//

#pragma once

#include <string>

#include <bridge/NativeObject.h>

class Screen
{
public:
	Screen(const std::string& screenName);

	Screen(const std::string& screenName, NativeObject&& nativeObject);

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

	enum class State
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

	NativeObject& getNativeScreen()
	{
		return _screenNativeObject;
	}

private:
	State _state = State::EXIT;
	std::string _screenName;
	NativeObject _screenNativeObject;
};
