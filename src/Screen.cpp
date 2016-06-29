//
// Created by Dawid Drozd aka Gelldur on 08.03.16.
//

#include "Screen.h"

Screen::Screen(const std::string& screenName)
		: Screen(screenName, NativeObject("nullObject-screen:" + screenName, nullptr))
{
}

Screen::Screen(const std::string& screenName, NativeObject&& nativeObject)
		: _screenName(screenName)
		, _screenNativeObject(std::move(nativeObject))
{
}
