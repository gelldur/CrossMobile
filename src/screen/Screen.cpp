//
// Created by Dawid Drozd aka Gelldur on 08.03.16.
//

#include "Screen.h"

Screen::Screen(const std::string& screenName)
		: Screen(screenName, Nodect("nullObject-screen:" + screenName, nullptr))
{
}

Screen::Screen(const std::string& screenName, Nodect&& node)
		: _screenName(screenName)
		, _screenNativeObject(std::move(node))
{
}
