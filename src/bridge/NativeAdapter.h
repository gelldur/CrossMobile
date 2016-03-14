//
// Created by Dawid Drozd aka Gelldur on 06.02.16.
//

#pragma once

#include <string>
#include "NativeView.h"

class Screen;

class NativeAdapter
{
public:
	virtual ~NativeAdapter() = default;

	virtual void onStartScreen(Screen* screen) = 0;

	virtual NativeView* findViewByTag(const std::string& tag) = 0;
};


