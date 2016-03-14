//
// Created by Dawid Drozd aka Gelldur on 05.02.16.
//

#pragma once

#include <string>
#include <bridge/NativeAdapter.h>

class Application
{
public:
	Application(NativeAdapter* nativeAdapter);
	~Application() = default;

	virtual void onCreate();

	virtual void startScreen(const std::string& screenName);

protected:
	NativeAdapter* getNativeAdapter() const
	{
		return _nativeAdapter;
	}

private:
	NativeAdapter* _nativeAdapter;
};


