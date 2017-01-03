//
// Created by pingu on 1/14/16.
//

#pragma once

#include <string>

#include <component/Nodect.h>

class Screen
{
public:
	Screen(const std::string& screenName);

	Screen(const std::string& screenName, Nodect&& node);

	virtual ~Screen() = default;

	Screen(const Screen& other) = delete;
	Screen& operator=(const Screen& other) = delete;

	void onEnter()
	{
	}

	void onExit()
	{
	}

	/**
	 * On iOS onCreate is called when viewDidLoad()
	 */
	virtual void onCreate() = 0;

	/**
	 * On iOS onResume is called when viewWillAppear()
	 */
	virtual void onResume() = 0;

	/**
	 * On iOS onPause is called when viewWillDisappear()
	 */
	virtual void onPause() = 0;

	/**
	 * On iOS onDestroy is called when dealloc()
	 */
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

	Nodect& getNativeScreen()
	{
		return _screenNativeObject;
	}

private:
	State _state = State::EXIT;
	std::string _screenName;
	Nodect _screenNativeObject;
};
