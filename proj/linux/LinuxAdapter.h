//
// Created by Dawid Drozd aka Gelldur on 09.03.16.
//

#pragma once

#include <bridge/NativeAdapter.h>

class LinuxAdapter : public NativeAdapter
{

public:
	virtual void onStartScreen(Screen* screen) override
	{
	}

	virtual NativeView* findViewByTag(const std::string& tag) override
	{
		return nullptr;
	}
};


